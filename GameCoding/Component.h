#pragma once

class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Init() = 0;
	virtual void Update() = 0;

	inline shared_ptr<GameObject> GetGameObject();

protected:
	shared_ptr<GameObject> _owner;
};


shared_ptr<GameObject> Component::GetGameObject()
{
	return _owner;
}