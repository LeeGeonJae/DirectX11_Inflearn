#include "pch.h"
#include "GameObject.h"

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

	// Component(Transform) - Test
	_parent->AddChild(_transform);
	_transform->SetParent(_parent);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	Vec3 pos = _parent->GetPosition();
	pos.x += 0.001f;
	_parent->SetPosition(pos);

	Vec3 rotation = _parent->GetRotation();
	rotation.z += 0.01f;
	_parent->SetRotation(rotation);
	//Vec3 pos = _transform->GetPosition();
	//pos.x += 0.001f;
	//_transform->SetPosition(pos);

	_transformData.WorldTransform = _transform->GetWorldMatrix().Transpose();

	_constantBuffer->CopyData(_transformData);
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