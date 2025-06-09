#include "pch.h"
#include "Geometry.h"

namespace Geometry
{
	float ScreenWidth = 0;
	float ScreenHeight = 0;
	void Init(const float _ScreenWidth, const float _ScreenHeight)
	{
		ScreenWidth = _ScreenWidth;
		ScreenHeight = _ScreenHeight;
	}

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

	UVMeshData GenerateUVRect(const float _Width, const float _Height)
	{
		UVMeshData ReturnData;
		std::vector<UVVertex>& Vertices = ReturnData.Vertices;

		UVVertex V;

		const float X = (_Width / ScreenWidth);
		const float Y = (_Height / ScreenHeight);

		V.Pos = Vector3(-X, -Y, 0.0f);
		V.UV = Vector2(0.0f, 1.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(-X, Y, 0.0f);
		V.UV = Vector2(0.0f, 0.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(X, -Y, 0.0f);
		V.UV = Vector2(1.0f, 1.0f);
		Vertices.push_back(V);

		V.Pos = Vector3(X, Y, 0.0f);
		V.UV = Vector2(1.0f, 0.0f);
		Vertices.push_back(V);

		ReturnData.Indices = { 0, 1, 2, 1, 3, 2 };

		return ReturnData;
	}
}
