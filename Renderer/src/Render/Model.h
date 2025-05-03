#pragma once
#include "Renderer/src/Render/IDRGenerator.h"

namespace Graphics
{
	class ObjectData
	{
	public:
		ObjectData(IDRGenerator& _Generator, const std::vector<Graphics::CpuConstData>& _CpuConstData)
			: BeRender(true)
			, ConstBuffer(_Generator.GenerateConstBuffer(_CpuConstData))
		{
		}
		~ObjectData()
		{
		}

	public:
		void BindConstBuffer(UINT _StartSlot) const
		{
			ConstBuffer->VSSetConstBuffers(_StartSlot);
			ConstBuffer->PSSetConstBuffers(_StartSlot);
		}
		void UpdateConstBuffer() const
		{
			ConstBuffer->UpdateBuffer();
		}

		void SetRender(bool _BeRender) { BeRender = _BeRender; }
		bool IsRender() const { return BeRender; }

	private:
		RefCounterPtr<IConstBuffer> ConstBuffer;
		bool BeRender;
		// ·»´õ¸µ Å¸ÀÔ

	};

	class Model
	{
	public:
		Model(IDRGenerator& _Generator, void* _VertexData, size_t _VertexSize, size_t _NumOfVertex
			, void* _IndexData, size_t _IndexSize, size_t _NumOfIndex)
			: Mesh(_Generator.GenerateModel(_VertexData, _VertexSize, _NumOfVertex, _IndexData, _IndexSize, _NumOfIndex))
		{
		}
		~Model()
		{
			for (auto Iter = ObjectDatas.begin(); Iter != ObjectDatas.end(); ++Iter)
				if (*Iter)
					delete* Iter;
		}

	public:
		UINT AddObjectData(ObjectData* _ObjectData)
		{
			ObjectDatas.push_back(_ObjectData);
			return ObjectDatas.size() - 1;
		}

		void UpdateObjectDatas() const
		{
			for (const auto ObjectData : ObjectDatas)
				ObjectData->UpdateConstBuffer();
		}

		void RenderModel(UINT _MeshDataStartSlot, UINT _ConstBufferStartSlot) const
		{
			Mesh->IASetBuffer(_MeshDataStartSlot);
			for (auto ObjectData : ObjectDatas)
			{
				if (!ObjectData->IsRender())
					continue;

				ObjectData->BindConstBuffer(_ConstBufferStartSlot);
				Mesh->DrawIndexed();
			}
		}

	private:
		RefCounterPtr<IMesh> Mesh;
		std::list<ObjectData*> ObjectDatas;

	};
}



