#pragma once
#include "ResourceBase.h"

struct Keyframe
{
    Vec2 offset = Vec2{ 0.f, 0.f };
    Vec2 size = Vec2{ 0.f, 0.f };
    float time = 0.f;
};

class Texture;

class Animation : public ResourceBase
{
    using Super = ResourceBase;
    
public:
    Animation();
    virtual ~Animation();

    virtual void Load(const wstring& path) override;
    virtual void Save(const wstring& path) override;

    inline void SetLoop(bool loop);
    inline bool IsLoop();
    inline void SetTexture(shared_ptr<Texture> texture);
    inline shared_ptr<Texture> GetTexture();
    inline Vec2 GetTextureSize();

    const Keyframe& GetKeyframe(int32 index);
    int32 GetKeyframeCount();
    void AddKeyframe(const Keyframe& keyframe);

private:
    bool _loop = false;
    shared_ptr<Texture> _texture;
    vector<Keyframe> _keyframes;
};

void Animation::SetLoop(bool loop)
{
    _loop = loop;
}
bool Animation::IsLoop()
{
    return _loop;
}
void Animation::SetTexture(shared_ptr<Texture> texture)
{
    _texture = texture;
}
shared_ptr<Texture> Animation::GetTexture()
{
    return _texture;
}
Vec2 Animation::GetTextureSize()
{
    return _texture->GetSize();
}