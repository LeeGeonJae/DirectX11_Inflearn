#pragma once

enum class ResourceType : uint8
{
	None = -1,
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,

	End
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<uint8>(ResourceType::End)
};

class ResourceBase : public enable_shared_from_this<ResourceBase>
{
public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase();

	inline ResourceType GetType();
	inline void SetName(const wstring& name);
	inline const wstring& GetName();
	inline uint32 GetID();

protected:
	virtual void Load(const wstring& path);
	virtual void Save(const wstring& path);

protected:
	ResourceType _type = ResourceType::None;
	wstring _name;
	wstring _path;
	uint32 _id = 0;

};

ResourceType ResourceBase::GetType()
{
	return _type;
}
void ResourceBase::SetName(const wstring& name)
{
	_name = name;
}
const wstring& ResourceBase::GetName()
{
	return _name;
}
uint32 ResourceBase::GetID()
{
	return _id;
}