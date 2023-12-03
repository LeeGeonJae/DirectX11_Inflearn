#pragma once
#include "Types.h"



struct CameraData
{
	Matrix View = Matrix::Identity;
	Matrix Projection = Matrix::Identity;
};
struct TransformData
{
	Matrix WorldTransform = Matrix::Identity;
};