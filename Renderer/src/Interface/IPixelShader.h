#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class IPixelShader : public RefCounter
	{
	public:
		IPixelShader() = default;
		virtual ~IPixelShader() = default;

	public:
		virtual void PSSetShader() = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXPixelShader : public IPixelShader
		{
		public:
			DXPixelShader(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<ID3D11PixelShader>& _PS)
				: Context(_Context)
				, PixelShader(_PS.Get())
			{
				PixelShader->AddRef();
			}
			~DXPixelShader()
			{
				PixelShader->Release();
			}

		public:
			void PSSetShader() override
			{
				Context->PSSetShader(PixelShader, nullptr, 0);
			}

		private:
			ID3D11PixelShader* PixelShader;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

