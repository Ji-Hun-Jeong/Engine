#include "pch.h"
#include "Geometry.h"

namespace Geometry
{
	ColorMeshData GenerateColorTriangle()
	{
		ColorMeshData ReturnData;
		std::vector<ColorVertex>& Vertices = ReturnData.Vertices;

		ColorVertex V;
		V.Pos = Vector3(-0.3f, -0.3f, 0.1f);
		V.Color = Vector3(1.0f, 0.0f, 0.0f);
		Vertices.push_back(V);
		V.Pos = Vector3(0.0f, 0.3f, 0.1f);
		V.Color = Vector3(0.0f, 1.0f, 0.0f);
		Vertices.push_back(V);
		V.Pos = Vector3(0.3f, -0.3f, 0.1f);
		V.Color = Vector3(0.0f, 0.0f, 1.0f);
		Vertices.push_back(V);

		ReturnData.Indices = { 0,1,2 };

		return ReturnData;
	}
	UVMeshData GenerateUVRect(float _Size)
	{
		UVMeshData ReturnData;
		std::vector<UVVertex>& Vertices = ReturnData.Vertices;

		UVVertex V;

		V.Pos = Vector3(-_Size, -_Size, 0.0f);
		V.UV = Vector2(0.0f, 1.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(-_Size, _Size, 0.0f);
		V.UV = Vector2(0.0f, 0.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(_Size, -_Size, 0.0f);
		V.UV = Vector2(1.0f, 1.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(_Size, _Size, 0.0f);
		V.UV = Vector2(1.0f, 0.0f);
		Vertices.push_back(V);

		ReturnData.Indices = { 0, 1, 2, 1, 3, 2 };

		return ReturnData;
	}
	UVMeshData GenerateUVRect(const float _Width, const float _Height, const float _ScreenWidth, const float _ScreenHeight)
	{
		const float Aspect = _ScreenWidth / _ScreenHeight;

		UVMeshData ReturnData;
		std::vector<UVVertex>& Vertices = ReturnData.Vertices;

		UVVertex V;

		V.Pos = Vector3(-Aspect, -1.0f, 0.0f);
		V.UV = Vector2(0.0f, 1.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(-Aspect, 1.0f, 0.0f);
		V.UV = Vector2(0.0f, 0.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(Aspect, -1.0f, 0.0f);
		V.UV = Vector2(1.0f, 1.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(Aspect, 1.0f, 0.0f);
		V.UV = Vector2(1.0f, 0.0f);
		Vertices.push_back(V);

		ReturnData.Indices = { 0, 1, 2, 1, 3, 2 };

		return ReturnData;
	}
}
