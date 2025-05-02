#include "pch.h"
#include "Geometry.h"

namespace Graphics
{
	namespace Geometry
	{
		RENDERER_API ColorMeshData GenerateColorTriangle()
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
	}
}