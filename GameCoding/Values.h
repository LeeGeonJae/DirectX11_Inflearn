#pragma once
#include "Types.h"

const int32 GWinSizeX = 800;
const int32 GWinSizeY = 600;

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