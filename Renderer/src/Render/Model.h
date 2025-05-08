#pragma once
#include "IRenderInterface.h"

namespace Graphics
{
	class Model
	{
	public:
		Model(RefCounterPtr<IMesh>& _Mesh)
			: Mesh(_Mesh)
		{
		}
		~Model()
		{
		}

	public:
		void AddRenderInterface(std::shared_ptr<IRenderInterface>& _RenderInterface)
		{
			RenderInterfaces.push_back(_RenderInterface);
		}

		void RenderModel(UINT _MeshDataStartSlot, UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot)
		{
			Mesh->IASetBuffer(_MeshDataStartSlot);
			for (auto Iter = RenderInterfaces.begin(); Iter != RenderInterfaces.end();)
			{
				auto& RenderInterface = *Iter;
				// �׻� Render�������̽��� ������Ʈ�� �������ֱ� ������ RefCount�� 1�̶�°��� �� ������Ʈ�� �������� ���ȴٴ� ��.
				if (Iter->use_count() == 1)
				{
					RenderInterface.reset();
					Iter = RenderInterfaces.erase(Iter);
				}
				else
				{
					RenderInterface->BindResourceToPipeline(_ConstBufferStartSlot, _ShaderResourceStartSlot);
					Mesh->DrawIndexed();
					++Iter;
				}
			}
		}

	private:
		RefCounterPtr<IMesh> Mesh;

		std::list<std::shared_ptr<IRenderInterface>> RenderInterfaces;

	};
}