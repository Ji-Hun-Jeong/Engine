#pragma once

namespace Graphics
{
	class RENDERER_API GraphicResourceMgr
	{
	public:
		GraphicResourceMgr() = default;
		~GraphicResourceMgr() = default;

	public:
		RefCounterPtr<class IMesh> AddMesh(const Str::FString& _Name, RefCounterPtr<class IMesh>& _Mesh)
		{
			auto Iter = Meshes.insert(std::make_pair(_Name, _Mesh));
			if (Iter.second)
				return _Mesh;
			else
				return Iter.first->second;
		}

		RefCounterPtr<class IMesh> GetMesh(const Str::FString& _Name)
		{
			auto Iter = Meshes.find(_Name);
			if (Iter == Meshes.end())
				return nullptr;
			return Iter->second;
		}

		RefCounterPtr<class ITopology> AddTopology(const Str::FString& _Name, RefCounterPtr<class ITopology>& _Topology)
		{
			auto Iter = Topologys.insert(std::make_pair(_Name, _Topology));
			if (Iter.second)
				return _Topology;
			else
				return Iter.first->second;
		}

		RefCounterPtr<class ITopology> GetTopology(const Str::FString& _Name)
		{
			auto Iter = Topologys.find(_Name);
			if (Iter == Topologys.end())
				return nullptr;
			return Iter->second;
		}

		RefCounterPtr<class IVertexShader> AddVertexShader(const Str::FString& _Name, RefCounterPtr<class IVertexShader>& _VertexShader)
		{
			auto Iter = VertexShaders.insert(std::make_pair(_Name, _VertexShader));
			if (Iter.second)
				return _VertexShader;
			else
				return Iter.first->second;
		}

		RefCounterPtr<class IVertexShader> GetVertexShader(const Str::FString& _Name)
		{
			auto Iter = VertexShaders.find(_Name);
			if (Iter == VertexShaders.end())
				return nullptr;
			return Iter->second;
		}

		RefCounterPtr<class IPixelShader> AddPixelShader(const Str::FString& _Name, RefCounterPtr<class IPixelShader>& _PixelShader)
		{
			auto Iter = PixelShaders.insert(std::make_pair(_Name, _PixelShader));
			if (Iter.second)
				return _PixelShader;
			else
				return Iter.first->second;
		}

		RefCounterPtr<class IPixelShader> GetPixelShader(const Str::FString& _Name)
		{
			auto Iter = PixelShaders.find(_Name);
			if (Iter == PixelShaders.end())
				return nullptr;
			return Iter->second;
		}

		RefCounterPtr<class IShaderResource> AddShaderResource(const Str::FString& _Name, RefCounterPtr<class IShaderResource>& _ShaderResource)
		{
			auto Iter = ShaderResources.insert(std::make_pair(_Name, _ShaderResource));
			if (Iter.second)
				return _ShaderResource;
			else
				return Iter.first->second;
		}

		RefCounterPtr<class IShaderResource> GetShaderResource(const Str::FString& _Name)
		{
			auto Iter = ShaderResources.find(_Name);
			if (Iter == ShaderResources.end())
				return nullptr;
			return Iter->second;
		}

	private:
		std::map<Str::FString, RefCounterPtr<class IMesh>> Meshes;
		std::map<Str::FString, RefCounterPtr<class ITopology>> Topologys;
		std::map<Str::FString, RefCounterPtr<class IVertexShader>> VertexShaders;
		std::map<Str::FString, RefCounterPtr<class IPixelShader>> PixelShaders;
		std::map<Str::FString, RefCounterPtr<class IShaderResource>> ShaderResources;
	};

	extern std::shared_ptr<class Model> RENDERER_API MakeModel(GraphicResourceMgr& _GRM, const Str::FString& _MeshName, const Str::FString& _TopologyName
		, const Str::FString& _VSName, const Str::FString& _PSName);
}


