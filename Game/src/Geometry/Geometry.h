#pragma once

struct ColorVertex
{
	Vector3 Pos;
	Vector3 Color;
};
struct UVVertex
{
	Vector3 Pos;
	Vector2 UV;
};
namespace Geometry
{
	struct ColorMeshData
	{
		std::vector<ColorVertex> Vertices;
		std::vector<uint8_t> Indices;
	};
	struct UVMeshData
	{
		std::vector<UVVertex> Vertices;
		std::vector<uint32_t> Indices;
	};
	extern ColorMeshData GenerateColorTriangle();
	extern UVMeshData GenerateUVRect(float _Size);
	extern UVMeshData GenerateUVRect(const float _Width, const float _Height, const float _ScreenWidth, const float _ScreenHeight);
}

