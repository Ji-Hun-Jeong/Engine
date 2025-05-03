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
		{

		}
		~IModelRegistry()
		{
			for (auto Model : Models)
				if (Model)
					delete Model;
			for (auto ConstBuffer : GlobalConstBuffers)
				if (ConstBuffer)
					ConstBuffer->Release();
		}

	public:
		UINT AddModel(Model* _Model)
		{
			Models.push_back(_Model);
			return Models.size();
		}

		UINT AddGlobalConstBuffer(IConstBuffer* _GlobalConstBuffer)
		{
			_GlobalConstBuffer->AddRef();
			GlobalConstBuffers.push_back(_GlobalConstBuffer);
			return GlobalConstBuffers.size();
		}

		std::list<Model*>& GetModels() { return Models; }
		std::list<IConstBuffer*>& GetGlobalConstBuffers() { return GlobalConstBuffers; }

	private:
		std::list<Model*> Models;
		std::list<IConstBuffer*> GlobalConstBuffers;

	};
}

