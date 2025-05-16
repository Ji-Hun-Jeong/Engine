#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class RENDERER_API IRasterizerState : public RefCounter
	{
	public:
		IRasterizerState() = default;
		virtual ~IRasterizerState() = default;

	public:
		virtual void RSSetState() const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXRasterizerState : public IRasterizerState
		{
		public:
			DXRasterizerState(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<ID3D11RasterizerState>& _RS)
				: Context(_Context)
				, RasterizerState(_RS.Get())
			{
				RasterizerState->AddRef();
			}
			~DXRasterizerState()
			{
				RasterizerState->Release();
			}

		public:
			void RSSetState() const override
			{
				Context->RSSetState(RasterizerState);
			}

		private:
			ID3D11RasterizerState* RasterizerState;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

