#include "pch.h"
#include "MeshRenderer.h"

#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "Game.h"
#include "Pipeline.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:Super(ComponentType::MeshRenderer)
	, _device(device)
{

}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	//Render(GGame->GetPipeline());
}