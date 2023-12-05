#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(ComPtr<ID3D11Device> device)
	: Super(ResourceType::Mesh)
	, _device(device)
{
}

Mesh::~Mesh()
{
}

void Mesh::CreateDefalutRectangle()
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	// VertexBuffer
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	// indexBuffer
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());
}
