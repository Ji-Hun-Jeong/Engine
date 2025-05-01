#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class IDraw
	{
	public:
		IDraw() {}
		virtual ~IDraw() {}

	public:
		virtual void DrawIndexed(UINT _IndexCount) = 0;
		virtual void Present() = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXDraw : public IDraw
		{
		public:
			DXDraw(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<IDXGISwapChain>& _SwapChain)
				: Context(_Context)
				, SwapChain(_SwapChain)
			{}
			~DXDraw()
			{}

		public:
			void DrawIndexed(UINT _IndexCount) override
			{
				Context->DrawIndexed(_IndexCount, 0, 0);
			}

			void Present() override
			{
				SwapChain->Present(1, 0);
			}
		private:
			
			ComPtr<ID3D11DeviceContext> Context;
			ComPtr<IDXGISwapChain> SwapChain;
		};
	}
}

