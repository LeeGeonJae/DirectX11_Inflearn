#include "pch.h"
#include "MeshRenderer.h"

#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "Game.h"
#include "Pipeline.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:Super(ComponentType::MeshRenderer)
	, _device(device)
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	// VertexBuffer
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	// indexBuffer
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());

	// vertexShader
	_vertexShader = make_shared <VertexShader>(_device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	// inputLayout
	_inputLayout = make_shared<InputLayout>(_device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	// pixelShader
	_pixelShader = make_shared <PixelShader>(_device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	// rasterizerState
	_rasterizerState = make_shared <RasterizerState>(_device);
	_rasterizerState->Create();

	// blendState
	_blendState = make_shared <BlendState>(_device);
	_blendState->Create();

	// ConstantBuffer
	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(_device, deviceContext);
	_cameraBuffer->Create();

	_TransformBuffer = make_shared<ConstantBuffer<TransformData>>(_device, deviceContext);
	_TransformBuffer->Create();

	// ShaderResourceView
	_texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"Skeleton.png");

	// SampleState
	_samplerState = make_shared <SamplerState>(_device);
	_samplerState->Create();
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	_cameraData.View = Camera::S_MatView.Transpose();
	_cameraData.Projection = Camera::S_MatProjection.Transpose();
	_cameraBuffer->CopyData(_cameraData);

	_transformData.WorldTransform = GetTransform()->GetWorldMatrix().Transpose();
	_TransformBuffer->CopyData(_transformData);

	Render(GGame->GetPipeline());
}

void MeshRenderer::Render(shared_ptr<Pipeline> pipeline)
{
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;

	pipeline->UpdatePipeline(info);
	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetindexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);
	pipeline->SetConstantBuffer(1, SS_VertexShader, _TransformBuffer);

	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
