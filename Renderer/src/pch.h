#pragma once
#include <Windows.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Renderer/include/SimpleMath.h"

#ifdef RENDERER_DEFINE
	#define RENDERER_API __declspec(dllexport)
#else
	#define RENDERER_API __declspec(dllimport)
#endif

using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Matrix;

struct Vertex
{
	Vector3 pos;
	Vector3 color;
};
