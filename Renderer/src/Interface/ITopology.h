#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	enum class eTopology
	{
		Triangle, End,
	};
	class ITopology
	{
	public:
		ITopology() = default;
		virtual ~ITopology() = default;

	public:
		virtual void IASetPrimitiveTopology() = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXTopology : public ITopology
		{
		public:
			DXTopology(ComPtr<ID3D11DeviceContext>& _Context, D3D11_PRIMITIVE_TOPOLOGY _TL)
				: Context(_Context)
				, Topology(_TL)
			{}
			~DXTopology()
			{}

		public:
			void IASetPrimitiveTopology() override
			{
				Context->IASetPrimitiveTopology(Topology);
			}

		private:
			D3D11_PRIMITIVE_TOPOLOGY Topology;
			ComPtr<ID3D11DeviceContext> Context;
		};
	}

}

