#pragma once
#include <Windows.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <queue>
#include <map>
#include <array>
#include <set>
#include "include/SimpleMath.h"
#include "Renderer/include/RefPtr.h"
#include "Renderer/include/RefCounter.h"
#include "FString.h"

#ifdef RENDERER_DEFINE
	#define RENDERER_API __declspec(dllexport)
#else
	#define RENDERER_API __declspec(dllimport)
#endif

using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Matrix;

struct RENDERER_API BufferDesc
{
	void* Data = nullptr;
	UINT ElementSize = 0;
	UINT NumOfElement = 0;
};