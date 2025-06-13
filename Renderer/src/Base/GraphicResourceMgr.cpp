#include "pch.h"
#include "GraphicResourceMgr.h"
#include "Render/Model.h"

namespace Graphics
{
	std::shared_ptr<Model> MakeModel(GraphicResourceMgr& _GRM, const Str::FString& _MeshName, const Str::FString& _TopologyName
		, const Str::FString& _VSName, const Str::FString& _PSName)
	{
		auto Mesh = _GRM.GetMesh("BasicRect");
		auto Topology = _GRM.GetTopology("Triangle");
		auto VS = _GRM.GetVertexShader("ImageVS");
		auto PS = _GRM.GetPixelShader("ImagePS");
		return std::make_shared<Model>(Mesh, Topology, VS, PS);
	}

}
