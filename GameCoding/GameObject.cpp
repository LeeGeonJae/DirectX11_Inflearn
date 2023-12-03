#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device)
	, _deviceContext(deviceContext)
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
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_constantBuffer->Create();

	// ShaderResourceView
	_texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"Skeleton.png");

	// SampleState
	_samplerState = make_shared <SamplerState>(_device);
	_samplerState->Create();
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Init();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		if (script)
			script->Init();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		if (script)
			script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		if (script)
			script->Update();
	}

	Vec3 pos = _transform->GetPosition();
	pos.x += 0.001f;
	_transform->SetPosition(pos);

	_transformData.WorldTransform = GetTransform()->GetWorldMatrix().Transpose();

	_constantBuffer->CopyData(_transformData);
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		if (script)
			script->LateUpdate();
	}
}

void GameObject::FixedUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->FixedUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		if (script)
		script->FixedUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
	return dynamic_pointer_cast<Transform>(component);
}

shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		shared_ptr<Transform> transform = make_shared<Transform>();
		//AddComponent(transform);
	}

	return GetTransform();
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	// shared_from_this 는 생성자에서만 생성하지 않으면 됩니다.
	// this 포인터를 넘겨주는 것이 아니라 shared_ptr로 포인터를 변환해서 this를 넘겨주는 함수
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
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
	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}