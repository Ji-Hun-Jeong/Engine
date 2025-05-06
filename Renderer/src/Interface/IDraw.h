#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class IPresenter : public RefCounter
	{
	public:
		IPresenter() {}
		virtual ~IPresenter() {}

	public:
		virtual void Present() const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXPresenter : public IPresenter
		{
		public:
			DXPresenter(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<IDXGISwapChain>& _SwapChain)
				: Context(_Context)
				, SwapChain(_SwapChain)
			{}
			~DXPresenter()
			{}

		public:
			void Present() const override
			{
				SwapChain->Present(1, 0);
			}

		private:
			ComPtr<ID3D11DeviceContext>& Context;
			ComPtr<IDXGISwapChain>& SwapChain;

		};
	}
}

