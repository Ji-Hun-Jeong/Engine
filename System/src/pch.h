#pragma once

#include <Windows.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>
#include <array>
#include <queue>

#include "Define.h"

namespace Utility
{
	template <typename T>
	void ClearVector(std::vector<T>& _Vector)
	{
		for (auto iter = _Vector.begin(); iter != _Vector.end(); ++iter)
			if (*iter)
				delete* iter;
		_Vector.clear();
	}
	template <typename T>
	void ClearList(std::list<T>& _List)
	{
		for (auto iter = _List.begin(); iter != _List.end(); ++iter)
			if (*iter)
				delete* iter;
		_List.clear();
	}
	template <typename T1, typename T2>
	void ClearMap(std::map<T1, T2>& _Map)
	{
		for (auto iter = _Map.begin(); iter != _Map.end(); ++iter)
			if (iter->second)
				delete iter->second;
		_Map.clear();
	}
}