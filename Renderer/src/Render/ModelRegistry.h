#pragma once
#include <list>
#include "Renderer/src/Interface/IModel.h"
#include "Renderer/src/Interface/IConstBuffer.h"

namespace Graphics
{
	// �̰͵� ������ ������ Ʈ�������� ������ �������̽��� ����?
	class RENDERER_API IModelRegistry
	{
	public:
		IModelRegistry()
		{

		}
		~IModelRegistry()
		{
			for (auto Model : Models)
				if (Model)
					Model->Release();
			for (auto ConstBuffer : ConstBuffers)
				if (ConstBuffer)
					ConstBuffer->Release();
		}

	public:
		UINT AddModel(IModel* _Model)
		{
			_Model->AddRef();
			Models.push_back(_Model);
			return Models.size();
		}
		UINT AddConstBuffer(IConstBuffer* _ConstBuffer)
		{
			_ConstBuffer->AddRef();
			ConstBuffers.push_back(_ConstBuffer);
			return ConstBuffers.size();
		}

		std::list<IModel*>& GetModels() { return Models; }
		std::list<IConstBuffer*>& GetConstBuffers() { return ConstBuffers; }

	private:
		std::list<IModel*> Models;
		std::list<IConstBuffer*> ConstBuffers;

	};
}

