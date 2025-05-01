#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class IRasterizerState
	{
	public:
		IRasterizerState() = default;
		virtual ~IRasterizerState() = default;

	public:
		virtual void RSSetState() = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXRasterizerState : public IRasterizerState
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
			void RSSetState() override
			{
				Context->RSSetState(RasterizerState);
			}

		private:
			ID3D11RasterizerState* RasterizerState;
			ComPtr<ID3D11DeviceContext> Context;
		};
	}

}

