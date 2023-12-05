#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
	using Super = ResourceBase;

public:
	Texture(ComPtr<ID3D11Device> device);
	~Texture();

	ComPtr< ID3D11ShaderResourceView> GetComPtr() {	return _shaderResourceView; }

	void Create(const wstring& path);

	inline Vec2 GetSize();

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	Vec2 _size = { 0.f, 0.f };
};

Vec2 Texture::GetSize()
{
	return _size;
}