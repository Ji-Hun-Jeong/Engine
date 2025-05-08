#pragma once
#include "Renderer/src/Render/IDRGenerator.h"

namespace Graphics
{
	class ObjectInterface
	{
	public:
		ObjectInterface(RefCounterPtr<IConstBuffer>& _ConstBuffer)
			: ConstBuffer(_ConstBuffer)
			, BeRender(true)
		{
		}
		~ObjectInterface()
		{
		}

	public:
		void UpdateConstBuffer() const
		{
			ConstBuffer->UpdateBuffer();
		}

		void SetData(UINT _StartSlot) const
		{
			if (!BeRender)
				return;

			ConstBuffer->VSSetConstBuffers(_StartSlot);
			ConstBuffer->PSSetConstBuffers(_StartSlot);
		}

		void SetRender(bool _BeRender) { BeRender = _BeRender; }
		bool IsRender() const { return BeRender; }

	private:
		RefCounterPtr<IConstBuffer> ConstBuffer;

		bool BeRender;
		// ∑ª¥ı∏µ ≈∏¿‘

	};

	class Model
	{
	public:
		Model(RefCounterPtr<IMesh>& _Mesh)
			: Mesh(_Mesh)
		{}
		~Model()
		{}

	public:
		UINT AddObjectData(std::shared_ptr<ObjectInterface>& _ObjectData)
		{
			ObjectDatas.push_back(_ObjectData);
			return ObjectDatas.size() - 1;
		}

		void RenderModel(UINT _MeshDataStartSlot, UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const
		{
			Mesh->IASetBuffer(_MeshDataStartSlot);
			for (auto& ObjectData : ObjectDatas)
			{
				ObjectData->SetData(_ConstBufferStartSlot);
				Mesh->DrawIndexed();
			}
		}

	private:
		RefCounterPtr<IMesh> Mesh;
		std::list<std::shared_ptr<ObjectInterface>> ObjectDatas;

	};
}