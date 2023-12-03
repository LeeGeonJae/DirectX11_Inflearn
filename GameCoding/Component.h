#pragma once
#include "GameObject.h"


class Component
{
public:
	Component(ComponentType type);
	virtual ~Component();

	virtual void Init() {}
	virtual void Start() {}
	virtual void Update() {}		// 몬스터, 플레이어
	virtual void LateUpdate() {}	// 카메라
	virtual void FixedUpdate() {}

public:
	inline ComponentType GetType();
	inline shared_ptr<GameObject> GetGameObject();
	inline shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	inline void SetGameObject(shared_ptr<GameObject> gameObject);

protected:
	ComponentType _type;
	weak_ptr<GameObject> _gameObject;
};

ComponentType Component::GetType()
{
	return _type;
}

shared_ptr<GameObject> Component::GetGameObject()
{
	return _gameObject.lock();
}

shared_ptr<Transform> Component::GetTransform()
{
	return _gameObject.lock()->GetTransform();
}

void Component::SetGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObject = gameObject;
}