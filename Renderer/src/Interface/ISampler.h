#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class ISampler : public RefCounter
	{
	public:
		ISampler() = default;
		virtual ~ISampler() = default;

	public:
		

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXSampler : public ISampler
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
			void VSSetSampler(UINT _StartSlot, UINT _NumSamplers)
			{
				Context->VSSetSamplers(_StartSlot, _NumSamplers, Samplers.data());
			}
			void PSSetSampler(UINT _StartSlot, UINT _NumSamplers)
			{
				Context->PSSetSamplers(_StartSlot, _NumSamplers, Samplers.data());
			}

		private:
			std::vector<ID3D11SamplerState*> Samplers;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

