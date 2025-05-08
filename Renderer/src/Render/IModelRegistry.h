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
		{}
		~IModelRegistry()
		{}

	public:
		void AddModel(std::shared_ptr<Model>& _Model)
		{
			Models.push_back(_Model);
		}
	
		std::list<std::shared_ptr<Model>>& GetModels() { return Models; }

	private:
		std::list<std::shared_ptr<Model>> Models;

	};
}