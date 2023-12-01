#pragma once
#include "Component.h"

class Transform : Component
{
public:
	Transform();
	~Transform();

public:
	virtual void Init() override;
	virtual void Update() override;

	void UpdateTransform();

	// Local
	inline Vec3 GetLocalScale();
	inline void SetLocalScale(const Vec3 localScale);
	inline Vec3 GetLocalRotation();
	inline void SetLocalRotation(const Vec3 localRotation);
	inline Vec3 GetLocalPosition();
	inline void SetLocalPosition(const Vec3 localPosition);

	// World
	inline Vec3 GetScale();
	void SetScale(const Vec3& worldScale);
	inline Vec3 GetRotation();
	void SetRotation(const Vec3& worldRotation);
	inline Vec3 GetPosition();
	void SetPosition(const Vec3& worldPosition);

	inline Matrix GetWorldMatrix();

	// °èÃþ °ü°è
	inline bool HasParent();

	inline shared_ptr<Transform> GetParent();
	inline void SetParent(shared_ptr<Transform> parent);

	inline const vector<shared_ptr<Transform>>& GetChildren();
	inline void AddChild(shared_ptr<Transform> child);

private:
	Vec3 _localPosition = { 0.f, 0.f, 0.f };
	Vec3 _localRotation = { 0.f, 0.f, 0.f };
	Vec3 _localScale = { 1.f, 1.f, 1.f };

	// Cache
	Matrix _local = Matrix::Identity;
	Matrix _world = Matrix::Identity;

	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _position;

	Vec3 _right;
	Vec3 _up;
	Vec3 _look;

private:
	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};

// Local
Vec3 Transform::GetLocalScale()
{
	return _localScale;
}
void Transform::SetLocalScale(const Vec3 localScale)
{
	_localScale = localScale;
	UpdateTransform();
}
Vec3 Transform::GetLocalRotation()
{
	return _localRotation;
}
void Transform::SetLocalRotation(const Vec3 localRotation)
{
	_localRotation = localRotation;
	UpdateTransform();
}
Vec3 Transform::GetLocalPosition()
{
	return _localPosition;
}
void Transform::SetLocalPosition(const Vec3 localPosition)
{
	_localPosition = localPosition;
	UpdateTransform();
}


// World
Vec3 Transform::GetScale()
{
	return _scale;
}
Vec3 Transform::GetRotation()
{
	return _rotation;
}
Vec3 Transform::GetPosition()
{
	return _position;
}
Matrix Transform::GetWorldMatrix()
{
	return _world;
}


// °èÃþ °ü°è
bool Transform::HasParent()
{
	return _parent != nullptr;
}
shared_ptr<Transform> Transform::GetParent()
{
	return _parent;
}
void Transform::SetParent(shared_ptr<Transform> parent)
{
	_parent = parent;
}
const vector<shared_ptr<Transform>>& Transform::GetChildren()
{
	return _children;
}
void Transform::AddChild(shared_ptr<Transform> child)
{
	_children.push_back(child);
}