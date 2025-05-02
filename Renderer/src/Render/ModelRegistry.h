#pragma once
#include <list>
#include "Renderer/src/Interface/IModel.h"
#include "Renderer/src/Interface/IConstBuffer.h"

namespace Graphics
{
	class ModelRegistry
	{
	public:
		ModelRegistry() = default;
		~ModelRegistry()
		{
			for (auto Model : Models)
				if (Model)
					Model->Release();
			for (auto ConstBuffer : ConstBuffers)
				if (ConstBuffer)
					ConstBuffer->Release();
		}

	public:
		void AddModel(IModel* _Model)
		{
			_Model->AddRef();
			Models.push_back(_Model);
		}
		void AddConstBuffer(IConstBuffer* _ConstBuffer)
		{
			_ConstBuffer->AddRef();
			ConstBuffers.push_back(_ConstBuffer);
		}
		std::list<IModel*>& GetModels() { return Models; }
		std::list<IConstBuffer*>& GetConstBuffers() { return ConstBuffers; }

	private:
		std::list<IModel*> Models;
		std::list<IConstBuffer*> ConstBuffers;

	};
}

