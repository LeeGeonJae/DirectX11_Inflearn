#pragma once
#include "ResourceBase.h"


class Shader : public ResourceBase
{
    using Super = ResourceBase;
public:
    Shader();
    virtual ~Shader();

public:
    inline shared_ptr<InputLayout> GetInputLayout();
    inline shared_ptr<VertexShader> GetVertexShader();
    inline shared_ptr<PixelShader> GetPixelShader();

private:
    friend class ResourceManager;

    shared_ptr<InputLayout> _inputLayout;
    shared_ptr<VertexShader> _vertexShader;
    shared_ptr<PixelShader> _pixelShader;
};

shared_ptr<InputLayout> Shader::GetInputLayout()
{
    return _inputLayout;
}
shared_ptr<VertexShader> Shader::GetVertexShader()
{
    return _vertexShader;
}
shared_ptr<PixelShader> Shader::GetPixelShader()
{
    return _pixelShader;
}
