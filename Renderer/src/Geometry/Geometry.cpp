#include "pch.h"
#include "Geometry.h"

namespace Graphics
{
	namespace Geometry
	{
		using DirectX::SimpleMath::Vector3;
		RENDERER_API MeshData GenerateSquare()
		{
			MeshData ReturnData;
			std::vector<Vertex>& Vertices = ReturnData.Vertices;

			Vertex V;
			V.pos = Vector3(-0.3f, -0.3f, 0.1f);
			V.color = Vector3(1.0f, 0.0f, 0.0f);
			Vertices.push_back(V);
			V.pos = Vector3(0.0f, 0.3f, 0.1f);
			V.color = Vector3(0.0f, 1.0f, 0.0f);
			Vertices.push_back(V);
			V.pos = Vector3(0.3f, -0.3f, 0.1f);
			V.color = Vector3(0.0f, 0.0f, 1.0f);
			Vertices.push_back(V);

			ReturnData.Indices = { 0,1,2 };

			return ReturnData;
		}
	}
}