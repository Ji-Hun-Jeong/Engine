#pragma once
#include "Renderer/src/Render/IDRGenerator.h"

namespace Graphics
{
	// 이걸 애니메이션과 스프라이트로 나누기?
	class StateContext
	{
	public:
		StateContext(IDRGenerator& _Generator, const std::vector<Graphics::CpuConstData>& _CpuConstData
			, const std::vector<Str::FString>& _Paths)
			: ConstBuffer(_Generator.GenerateConstBuffer(_CpuConstData))
			, ShaderResource(_Generator.GenerateShaderResource(_Paths))
		{

		}
		~StateContext() {}

	public:
		void UpdateConstBuffer() const
		{
			ConstBuffer->UpdateBuffer();
		}
		void BindContext(UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const
		{
			ConstBuffer->VSSetConstBuffers(_ConstBufferStartSlot);
			ConstBuffer->PSSetConstBuffers(_ConstBufferStartSlot);
			ShaderResource->VSSetShaderResources(_ShaderResourceStartSlot);
			ShaderResource->PSSetShaderResources(_ShaderResourceStartSlot);

		}

	private:
		RefCounterPtr<IConstBuffer> ConstBuffer;
		RefCounterPtr<IShaderResource> ShaderResource;

	};

	class ObjectData
	{
	public:
		ObjectData()
			: BeRender(true)
		{
		}
		~ObjectData()
		{
		}

	public:
		UINT AddStateContext(std::shared_ptr<StateContext>& _StateContext)
		{
			StateContexts.push_back(_StateContext);
			return StateContexts.size() - 1;
		}
		void UpdateConstBuffer() const
		{
			for (auto StateContext : StateContexts)
				StateContext->UpdateConstBuffer();
		}
		void SetData(UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const
		{
			if (!BeRender)
				return;

			for (auto StateContext : StateContexts)
				StateContext->BindContext(_ConstBufferStartSlot, _ShaderResourceStartSlot);
		}

		void SetRender(bool _BeRender) { BeRender = _BeRender; }
		bool IsRender() const { return BeRender; }

	private:
		std::vector<std::shared_ptr<StateContext>> StateContexts;
		bool BeRender;
		// 렌더링 타입

	};

	class Model
	{
	public:
		Model(IDRGenerator& _Generator, void* _VertexData, size_t _VertexSize, size_t _NumOfVertex
			, void* _IndexData, size_t _IndexSize, size_t _NumOfIndex)
			: Mesh(_Generator.GenerateModel(_VertexData, _VertexSize, _NumOfVertex, _IndexData, _IndexSize, _NumOfIndex))
		{}
		~Model()
		{}

	public:
		UINT AddObjectData(std::shared_ptr<ObjectData>& _ObjectData)
		{
			ObjectDatas.push_back(_ObjectData);
			return ObjectDatas.size() - 1;
		}

		void UpdateObjectDatas() const
		{
			for (const auto ObjectData : ObjectDatas)
				ObjectData->UpdateConstBuffer();
		}

		void RenderModel(UINT _MeshDataStartSlot, UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const
		{
			Mesh->IASetBuffer(_MeshDataStartSlot);
			for (auto ObjectData : ObjectDatas)
			{
				ObjectData->SetData(_ConstBufferStartSlot, _ShaderResourceStartSlot);
				Mesh->DrawIndexed();
			}
		}

	private:
		RefCounterPtr<IMesh> Mesh;
		std::list<std::shared_ptr<ObjectData>> ObjectDatas;

	};
}