#pragma once
#include <Windows.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <unordered_map>
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

enum class eCategoryVS
{
	Basic, End,
};
enum class eCategoryPS
{
	Basic, End,
};
enum class eCategorySS
{
	Linear, End,
};
enum class eCategoryRS
{
	SolidCw, End,
};
enum class eCategoryRTV
{
	BackBuffer, End,
};
enum class eCategoryDSS
{
	Basic, End,
};
enum class eCategoryDSV
{
	BackBuffer, End,
};
enum class eCategoryIL
{
	PosColor, End,
};
enum class eCategoryVP
{
	Basic, End,
};
enum class eCategoryTopology
{
	Triangle, End,
};