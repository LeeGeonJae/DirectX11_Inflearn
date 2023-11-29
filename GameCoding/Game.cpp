#include "pch.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);
	_vertexBuffer = make_shared<VertexBuffer>(_graphics->GetDevice());
	_indexBuffer = make_shared<IndexBuffer>(_graphics->GetDevice());
	_inputLayout = make_shared<InputLayout>(_graphics->GetDevice());
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexShader = make_shared <VertexShader>(_graphics->GetDevice());
	_pixelShader = make_shared <PixelShader>(_graphics->GetDevice());
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_texture1 = make_shared<Texture>(_graphics->GetDevice());

	_rasterizerState = make_shared <RasterizerState>(_graphics->GetDevice());
	_samplerState = make_shared <SamplerState>(_graphics->GetDevice());
	_blendState = make_shared <BlendState>(_graphics->GetDevice());

	_pipeline = make_shared <Pipeline>(_graphics->GetDeviceContext());


	// Geometry
	{
		GeometryHelper::CreateRectangle(_geometry);

		// VertexBuffer
		_vertexBuffer->Create(_geometry->GetVertices());
		// IndexBuffer
		_indexBuffer->Create(_geometry->GetIndices());
	}

	// VertexShader
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	// InputLayout
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	// PixelShader
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_rasterizerState->Create();
	_samplerState->Create();
	_blendState->Create();
		
	// ShaderResourceView ( texture )
	_texture1->Create(L"Skeleton.png");
	 
	// ConstantBuffer
	_constantBuffer->Create();
}

void Game::Update()
{
	// Scale Rotation Translation
	//_transformData.offset.x += 0.003f;
	//_transformData.offset.y += 0.003f;

	_constantBuffer->CopyData(_transformData);
}

void Game::Render()
{
	_graphics->RenderBegin();

	{
		PipelineInfo info;
		info.inputLayout = _inputLayout;
		info.vertexShader = _vertexShader;
		info.pixelShader = _pixelShader;
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;
		
		_pipeline->UpdatePipeline(info);
		_pipeline->SetVertexBuffer(_vertexBuffer);
		_pipeline->SetindexBuffer(_indexBuffer);
		_pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
		_pipeline->SetTexture(0, SS_PixelShader, _texture1);
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
		
		_pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
	}

	_graphics->RenderEnd();
}