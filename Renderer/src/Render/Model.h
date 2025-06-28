#pragma once
#include "IRenderInterface.h"

namespace Graphics
{
	class RENDERER_API Model
	{
	public:
		Model(RefCounterPtr<IMesh>& _Mesh, RefCounterPtr<ITopology>& _Topology, RefCounterPtr<IVertexShader>& _VertexShader
		, RefCounterPtr<IPixelShader>& _PixelShader)
			: Mesh(_Mesh), Topology(_Topology), VertexShader(_VertexShader), PixelShader(_PixelShader)
		{
		}
		~Model()
		{
			int a;
		}

	public:
		void AddRenderInterface(std::shared_ptr<IRenderInterface>& _RenderInterface)
		{
			RenderInterfaces.push_back(_RenderInterface);
		}

		void RenderModel(UINT _MeshDataStartSlot, UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot)
		{
			Topology->IASetPrimitiveTopology();
			VertexShader->IASetInputLayout();
			VertexShader->VSSetShader();
			PixelShader->PSSetShader();
			Mesh->IASetBuffer(_MeshDataStartSlot);
			for (auto Iter = RenderInterfaces.begin(); Iter != RenderInterfaces.end();)
			{
				auto& RenderInterface = *Iter;
				// 항상 Render인터페이스는 오브젝트도 가지고있기 때문에 RefCount가 1이라는것은 그 오브젝트가 소유권을 버렸다는 뜻.
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
		RefCounterPtr<ITopology> Topology;
		RefCounterPtr<IVertexShader> VertexShader;
		RefCounterPtr<IPixelShader> PixelShader;


		std::list<std::shared_ptr<IRenderInterface>> RenderInterfaces;

	};
}