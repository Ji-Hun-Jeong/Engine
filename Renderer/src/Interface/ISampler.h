#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class RENDERER_API ISampler : public RefCounter
	{
	public:
		ISampler() = default;
		virtual ~ISampler() = default;

	public:
		virtual void VSSetSampler(UINT _StartSlot) const = 0;
		virtual void PSSetSampler(UINT _StartSlot) const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXSampler : public ISampler
		{
		public:
			DXSampler(ComPtr<ID3D11DeviceContext>& _Context, const std::vector<ComPtr<ID3D11SamplerState>>& _SS)
				: Context(_Context)
				, Samplers{}
			{
				for (auto& SS : _SS)
				{
					SS->AddRef();
					Samplers.push_back(SS.Get());
				}
			}
			~DXSampler()
			{
				for (auto SS : Samplers)
					SS->Release();
			}

		public:
			void VSSetSampler(UINT _StartSlot) const override
			{
				Context->VSSetSamplers(_StartSlot, Samplers.size(), Samplers.data());
			}
			void PSSetSampler(UINT _StartSlot) const override
			{
				Context->PSSetSamplers(_StartSlot, Samplers.size(), Samplers.data());
			}

		private:
			std::vector<ID3D11SamplerState*> Samplers;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

