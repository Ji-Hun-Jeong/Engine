#pragma once
#include <Windows.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Renderer/include/SimpleMath.h"
#include "Renderer/include/RefPtr.h"
#include "Renderer/include/RefCounter.h"

#include <System/src/pch.h>

#ifdef RENDERER_DEFINE
	#define RENDERER_API __declspec(dllexport)
#else
	#define RENDERER_API __declspec(dllimport)
#endif

using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Matrix;
