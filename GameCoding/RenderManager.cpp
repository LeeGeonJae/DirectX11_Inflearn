#include "pch.h"
#include "RenderManager.h"
#include "Pipeline.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Animator.h"

RenderManager::RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device)
	, _deviceContext(deviceContext)
{
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>(_deviceContext);

	// ConstantBuffer
	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(_device, _deviceContext);
	_cameraBuffer->Create();
	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_transformBuffer->Create();
	_animationBuffer = make_shared<ConstantBuffer<AnimationData>>(_device, _deviceContext);
	_animationBuffer->Create();

	_rasterizerState = make_shared <RasterizerState>(_device);
	_rasterizerState->Create();
	_blendState = make_shared <BlendState>(_device);
	_blendState->Create();
	_samplerState = make_shared <SamplerState>(_device);
	_samplerState->Create();
}

void RenderManager::Update(shared_ptr<Graphics> graphics)
{
	graphics->RenderBegin();

	PushCameraData();
	GetherRenderableObjects();
	RenderObjects();

	graphics->RenderEnd();
}

void RenderManager::PushCameraData()
{
	_cameraData.View = Camera::S_MatView;
	_cameraData.Projection = Camera::S_MatProjection;
	_cameraBuffer->CopyData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->CopyData(_transformData);
}

void RenderManager::PushAnimationData()
{
	_animationBuffer->CopyData(_animationData);
}

void RenderManager::GetherRenderableObjects()
{
	_renderObjects.clear();

	auto& gameObjects = GGame->GetSceneManager()->GetActiveScene()->GetGameObjects();
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = gameObject->GetMeshRenderer();
		if (meshRenderer)
			_renderObjects.push_back(gameObject);
	}
}

void RenderManager::RenderObjects()
{
	for (const shared_ptr<GameObject>& gameObject : _renderObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = gameObject->GetMeshRenderer();
		if (meshRenderer == nullptr)
			continue;

		shared_ptr<Transform> transform = gameObject->GetTransform();
		if (transform == nullptr)
			continue;

		// SRT
		_transformData.WorldTransform = transform->GetWorldMatrix();
		PushTransformData();
		
		// Animation
		shared_ptr<Animator> animator = gameObject->GetAnimator();
		if (animator)
		{
			const Keyframe& keyframe = animator->GetCurrentKeyframe();
			_animationData.spriteOffset = keyframe.offset;
			_animationData.spriteSize = keyframe.size;
			_animationData.TextureSize = animator->GetCurrentAnimation()->GetTextureSize();
			_animationData.useAnimation = 1.f;
			PushAnimationData();

			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, animator->GetCurrentAnimation()->GetTexture());
		}
		else
		{
			_animationData.spriteOffset = Vec2(0.f, 0.f);
			_animationData.spriteSize = Vec2(0.f, 0.f);
			_animationData.TextureSize = Vec2(0.f, 0.f);
			_animationData.useAnimation = 0.f;
			PushAnimationData();

			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
		}

		PipelineInfo info;
		info.inputLayout = meshRenderer->GetInputLayout();
		info.vertexShader = meshRenderer->GetVertexShader();
		info.pixelShader = meshRenderer->GetPixelShader();
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;

		_pipeline->UpdatePipeline(info);
		_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetindexBuffer(meshRenderer->GetMesh()->GetindexBuffer());
		
		_pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);
		_pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer);
		
		//_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
		
		_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetindexBuffer()->GetCount(), 0, 0);
	}
}