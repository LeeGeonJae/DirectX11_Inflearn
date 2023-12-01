#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Init()
{
}

void Transform::Update()
{
}

// 회전 행렬을 생성하는 함수
Vec3 quaternionToRotation(const Quaternion& quat)
{
	Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (quat.w * quat.x + quat.y * quat.z);
	double cosr_cosp = 1 - 2 * (quat.x * quat.x + quat.y * quat.y);
	angles.x = atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = sqrt(1 + 2 * (quat.w * quat.y - quat.x * quat.z));
	double cosp = sqrt(1 - 2 * (quat.w * quat.y - quat.x * quat.z));
	angles.y = 2 * atan2(sinp, cosp) - 3.141592f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (quat.w * quat.z + quat.x * quat.y);
	double cosy_cosp = 1 - 2 * (quat.y * quat.y + quat.z * quat.z);
	angles.z = atan2(siny_cosp, cosy_cosp);

	return angles;
}

void Transform::UpdateTransform()
{
	Matrix Scale = Matrix::CreateScale(_localScale);
	Matrix Rotation = Matrix::CreateRotationX(_localRotation.x);
	Rotation *= Matrix::CreateRotationY(_localRotation.y);
	Rotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix Translation = Matrix::CreateTranslation(_localPosition);

	_local = Scale * Rotation * Translation;

	if (HasParent())
	{
		_world = _local * _parent->GetWorldMatrix();
	}
	else
	{
		_world = _local;
	}

	Quaternion quat;

	_world.Decompose(_scale, quat, _position);
	_rotation = quaternionToRotation(quat);

	// TransformCoord
	// TransformNormal
	_right = Vec3::TransformNormal(Vec3::Right, _world);
	_up = Vec3::TransformNormal(Vec3::Up, _world);
	_look = Vec3::TransformNormal(Vec3::Backward, _world);

	// Children
	for (const shared_ptr<Transform>& child : _children)
	{
		child->UpdateTransform();
	}
}


void Transform::SetScale(const Vec3& worldScale)
{
	if (HasParent())
	{
		Vec3 parentScale = _parent->GetScale();
		Vec3 scale = worldScale;
		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;
		SetLocalScale(scale);
	}
	else
	{
		SetLocalScale(worldScale);
	}
}

void Transform::SetRotation(const Vec3& worldRotation)
{
	if (HasParent())
	{
		Matrix inverseMatrix = _parent->GetWorldMatrix().Invert();

		Vec3 rotaiton;
		rotaiton.TransformNormal(worldRotation, inverseMatrix);

		SetLocalRotation(rotaiton);
	}
	else
	{
		SetLocalRotation(worldRotation);
	}
}

void Transform::SetPosition(const Vec3& worldPosition)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();

		Vec3 position;
		position.Transform(worldPosition, worldToParentLocalMatrix);

		SetLocalPosition(position);
	}
	else
	{
		SetLocalPosition(worldPosition);
	}
}