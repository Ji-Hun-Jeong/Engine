#pragma once

namespace Graphics
{
	namespace Geometry
	{
		struct MeshData
		{
			std::vector<Vertex> Vertices;
			std::vector<uint32_t> Indices;
		};
		extern RENDERER_API MeshData GenerateSquare();
	}
}

