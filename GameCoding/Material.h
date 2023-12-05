#pragma once
#include "ResourceBase.h"

class Shader;
class Texture;

class Material : public ResourceBase
{
    using Super = ResourceBase;

public:
    Material();
    virtual ~Material();

    inline auto GetShader();
    inline auto GetTexture();

    inline void SetShader(shared_ptr<Shader> shader);
    inline void SetTexture(shared_ptr<Texture> texture);

private:
    shared_ptr<Shader> _shader;
    
    // 쉐이더에 넘기는 온갖 인자들
    shared_ptr<Texture> _texture;
};

auto Material::GetShader()
{
    return _shader;
}

auto Material::GetTexture()
{
    return _texture;
}

void Material::SetShader(shared_ptr<Shader> shader)
{
    _shader = shader;
}

void Material::SetTexture(shared_ptr<Texture> texture)
{
    _texture = texture;
}
