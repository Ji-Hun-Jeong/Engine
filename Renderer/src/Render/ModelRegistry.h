#pragma once
#include <list>
#include "Model.h"

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
					delete Model;
		}

	public:
		UINT AddModel(Model* _Model)
		{
			Models.push_back(_Model);
			return Models.size();
		}

		UINT AddGlobalConstBuffer(RefCounterPtr<IConstBuffer>& _GlobalConstBuffer)
		{
			GlobalConstBuffers.push_back(_GlobalConstBuffer);
			return GlobalConstBuffers.size();
		}

		std::list<Model*>& GetModels() { return Models; }
		std::list<RefCounterPtr<IConstBuffer>>& GetGlobalConstBuffers() { return GlobalConstBuffers; }

	private:
		std::list<Model*> Models;
		std::list<RefCounterPtr<IConstBuffer>> GlobalConstBuffers;

	};
}

