#pragma once
#include <list>
#include "Model.h"

namespace Graphics
{
	// 이것도 선형을 쓸건지 트리구조를 쓸건지 인터페이스로 제공?
	class RENDERER_API IModelRegistry
	{
	public:
		IModelRegistry()
		{}
		~IModelRegistry()
		{}

	public:
		UINT AddModel(std::shared_ptr<Model>& _Model)
		{
			Models.push_back(_Model);
			return Models.size();
		}

		UINT AddGlobalConstBuffer(RefCounterPtr<IConstBuffer>& _GlobalConstBuffer)
		{
			GlobalConstBuffers.push_back(_GlobalConstBuffer.Get());
			return GlobalConstBuffers.size();
		}

		std::list<std::shared_ptr<Model>>& GetModels() { return Models; }
		std::list<IConstBuffer*>& GetGlobalConstBuffers() { return GlobalConstBuffers; }

	private:
		std::list<std::shared_ptr<Model>> Models;
		std::list<IConstBuffer*> GlobalConstBuffers;

	};
}