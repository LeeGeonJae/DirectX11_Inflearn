#pragma once
#include "Component.h"

#include "Material.h"
#include "Shader.h"

class Mesh;
class Material;
class Shader;


class MeshRenderer : public Component
{
    using Super = Component;

public:
    MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
    virtual ~MeshRenderer();

public:
	virtual void Update() override;

	inline void SetMaterial(shared_ptr<Material> material);
	inline void SetShader(shared_ptr<Shader> shader);
	inline void SetMesh(shared_ptr<Mesh> mesh);
	inline void SetTexture(shared_ptr<Texture> texture);

	inline auto GetMaterial();
	inline auto GetVertexShader();
	inline auto GetInputLayout();
	inline auto GetPixelShader();

	inline shared_ptr<Mesh> GetMesh();
	inline shared_ptr<Texture> GetTexture();

private:
	ComPtr<ID3D11Device> _device;

	friend class RenderManager;

	// mesh
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
};

void MeshRenderer::SetMesh(shared_ptr<Mesh> mesh)
{
	_mesh = mesh;
}
void MeshRenderer::SetMaterial(shared_ptr<Material> material)
{
	_material = material;
}
void MeshRenderer::SetShader(shared_ptr<Shader> shader)
{
	_material->SetShader(shader);
}
void MeshRenderer::SetTexture(shared_ptr<Texture> texture)
{
	_material->SetTexture(texture);
}
auto MeshRenderer::GetMaterial()
{
	return _material;
}
auto MeshRenderer::GetVertexShader()
{
	return _material->GetShader()->GetVertexShader();
}
auto MeshRenderer::GetInputLayout()
{
	return _material->GetShader()->GetInputLayout();
}
auto MeshRenderer::GetPixelShader()
{
	return _material->GetShader()->GetPixelShader();
}

shared_ptr<Mesh> MeshRenderer::GetMesh()
{
	return _mesh;
}
shared_ptr<Texture> MeshRenderer::GetTexture()
{
	return _material->GetTexture();
}