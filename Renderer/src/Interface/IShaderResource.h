#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class RENDERER_API IShaderResource : public RefCounter
	{
	public:
		IShaderResource() = default;
		virtual ~IShaderResource() = default;

	public:
		virtual void VSSetShaderResources(UINT _StartSlot) const = 0;
		virtual void PSSetShaderResources(UINT _StartSlot) const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXShaderResource : public IShaderResource
		{
		public:
			DXShaderResource(ComPtr<ID3D11DeviceContext>& _Context, std::vector<ComPtr<ID3D11ShaderResourceView>>& _ShaderResourceViews)
				: Context(_Context)
				, ShaderResourceViews{}
			{
				ShaderResourceViews.reserve(_ShaderResourceViews.size());
				for (auto& SRV : _ShaderResourceViews)
				{
					SRV->AddRef();
					ShaderResourceViews.push_back(SRV.Get());
				}
			}
			~DXShaderResource()
			{
				for (auto SRV : ShaderResourceViews)
					SRV->Release();
			}

		public:
			void VSSetShaderResources(UINT _StartSlot) const override
			{
				Context->VSSetShaderResources(_StartSlot, ShaderResourceViews.size(), ShaderResourceViews.data());
			}
			void PSSetShaderResources(UINT _StartSlot) const override
			{
				Context->PSSetShaderResources(_StartSlot, ShaderResourceViews.size(), ShaderResourceViews.data());
			}

		private:
			std::vector<ID3D11ShaderResourceView*> ShaderResourceViews;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

