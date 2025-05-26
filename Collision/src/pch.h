#pragma once

#include <map>
#include <vector>

#include "include/SimpleMath.h"
#include "FString.h"

#ifdef COLLISION_DEFINE
	#define COLLISION_API __declspec(dllexport)
#else
	#define COLLISION_API __declspec(dllexport)
#endif

using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;