#pragma once

class GameObject;
class Transform;

enum class ComponentType
{
	Transform,
	MeshRenderer,
	Camera,
	Animator,
	// ...
	Script,

	End,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1,
};

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
	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

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
void Component::SetGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObject = gameObject;
}