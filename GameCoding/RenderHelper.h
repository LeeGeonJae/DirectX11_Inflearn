#pragma once

struct CameraData
{
	Matrix View = Matrix::Identity;
	Matrix Projection = Matrix::Identity;
};

struct TransformData
{
	Matrix WorldTransform = Matrix::Identity;
};

struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 TextureSize;
	float useAnimation;
	float padding;
};