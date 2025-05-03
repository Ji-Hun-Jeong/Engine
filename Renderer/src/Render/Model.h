#pragma once
#include "Renderer/src/Interface/IMesh.h"
#include "Renderer/src/Interface/IConstBuffer.h"

namespace Graphics
{
	class ObjectData
	{
	public:
		ObjectData()
			: IsRender(true)
		{}
		~ObjectData() 
		{
			for (auto ConstBuffer : ConstBuffers)
				ConstBuffer->Release();
		}

	public:
		std::vector<IConstBuffer*>& GetConstBuffers() { return ConstBuffers; }
		void AddConstBuffer(IConstBuffer* _ConstBuffer) 
		{
			_ConstBuffer->AddRef();
			ConstBuffers.push_back(_ConstBuffer); 
		}
		void SetRender(bool _IsRender) { IsRender = _IsRender; }

	private:
		std::vector<IConstBuffer*> ConstBuffers;
		bool IsRender;
		// ∑ª¥ı∏µ ≈∏¿‘

	};

	class Model
	{
	public:
		Model(IMesh& _Mesh)
			: Mesh(_Mesh)
		{
			Mesh.AddRef();
		}
		~Model()
		{
			if (&Mesh)
				Mesh.Release();

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

		IMesh& GetMesh() { return Mesh; }
		std::list<ObjectData*>& GetObjectDatas() { return ObjectDatas; }

	private:
		IMesh& Mesh;
		std::list<ObjectData*> ObjectDatas;

	};
}



