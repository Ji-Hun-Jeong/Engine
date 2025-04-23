#pragma once

struct ColorVertex
{
	Vector3 Pos;
	Vector3 Color;
};
namespace Graphics
{
	namespace Geometry
	{
		struct ColorMeshData
		{
			std::vector<ColorVertex> Vertices;
			std::vector<uint32_t> Indices;
		};

		extern RENDERER_API ColorMeshData GenerateColorTriangle();
	}
}

