#pragma once
#include <Windows.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "../include/SimpleMath.h"

#ifdef RENDERER_DEFINE
	#define RENDERER_API __declspec(dllexport)
#else
	#define RENDERER_API __declspec(dllimport)
#endif

