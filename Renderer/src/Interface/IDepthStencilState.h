#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class RENDERER_API IDepthStencilState : public RefCounter
	{
	public:
		IDepthStencilState() {}
		virtual ~IDepthStencilState() {}

	public:
		virtual void OMSetDepthStencilState(UINT _StencilRef) const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXDepthStencilState : public IDepthStencilState
		{
		public:
			DXDepthStencilState(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<ID3D11DepthStencilState>& _DSS)
				: Context(_Context)
				, DepthStencilState(_DSS.Get())
			{
				DepthStencilState->AddRef();
			}
			~DXDepthStencilState() 
			{
				DepthStencilState->Release();
			}

		public:
			void OMSetDepthStencilState(UINT _StencilRef) const override
			{
				Context->OMSetDepthStencilState(DepthStencilState, _StencilRef);
			}

		private:
			ID3D11DepthStencilState* DepthStencilState;
			ComPtr<ID3D11DeviceContext>& Context;

		};
	}
}

