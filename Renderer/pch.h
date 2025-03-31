#pragma once
#include <Windows.h>
#include <cassert>
#include <vector>
#include <iostream>
#include "include/SimpleMath.h"

#ifdef RENDERER_DEFINE
	#define RENDERER_API __declspec(dllexport)
#else
	#define RENDERER_API __declspec(dllimport)
#endif

struct Vertex
{
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 color;
};