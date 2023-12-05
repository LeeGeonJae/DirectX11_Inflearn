#pragma once
#include "ResourceBase.h"
class Mesh : public ResourceBase
{
    using Super = ResourceBase;

public:
    Mesh(ComPtr<ID3D11Device> device);
    virtual ~Mesh();

    void CreateDefalutRectangle();

    inline shared_ptr<VertexBuffer> GetVertexBuffer();
    inline shared_ptr<IndexBuffer> GetindexBuffer();

private:
    ComPtr<ID3D11Device> _device;

    // Mesh
    shared_ptr<Geometry<VertexTextureData>> _geometry;
    shared_ptr<VertexBuffer> _vertexBuffer;
    shared_ptr<IndexBuffer> _indexBuffer;
};

shared_ptr<VertexBuffer> Mesh::GetVertexBuffer()
{
    return _vertexBuffer;
}
shared_ptr<IndexBuffer> Mesh::GetindexBuffer()
{
    return _indexBuffer;
}