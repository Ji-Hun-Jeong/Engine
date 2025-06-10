#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class RENDERER_API IBlendState : public RefCounter
	{
	public:
		IBlendState() = default;
		virtual ~IBlendState() = default;

	public:
		virtual void OMSetBlendState() const = 0;

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXBlendState : public IBlendState
		{
		public:
			DXBlendState(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<ID3D11BlendState>& _BlendState, const float* _BlendFactor)
				: Context(_Context)
				, BlendState(_BlendState)
				, BlendFactor(0)
			{
				memcpy(BlendFactor, _BlendFactor, 4);
			}
			~DXBlendState() = default;

		public:
			void OMSetBlendState() const override
			{
				Context->OMSetBlendState(BlendState.Get(), BlendFactor, 0xffffffff);
			}

		private:
			ComPtr<ID3D11DeviceContext>& Context;
			ComPtr<ID3D11BlendState> BlendState;

			float BlendFactor[4];
		};
	}

}

