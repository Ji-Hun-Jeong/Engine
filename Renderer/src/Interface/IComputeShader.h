#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class RENDERER_API IComputeShader : public RefCounter
	{
	public:
		IComputeShader() = default;
		virtual ~IComputeShader() = default;

	public:
		virtual void CSSetShader() = 0;
		virtual void ComputeShaderBarrier() = 0;
		virtual void Dispatch(UINT _ThreadGroupCountX, UINT _ThreadGroupCountY, UINT _ThreadGroupCountZ) = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXComputeShader : public IComputeShader
		{
		public:
			DXComputeShader(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<ID3D11ComputeShader>& _ComputeShader)
				: Context(_Context)
				, ComputeShader(_ComputeShader)
			{

			}
			~DXComputeShader()
			{

			}

		public:
			void CSSetShader() override
			{
				Context->CSSetShader(ComputeShader.Get(), nullptr, 0);
			}

			void ComputeShaderBarrier() override
			{
				/*ID3D11ShaderResourceView* NullSRV[6] = { nullptr };
				Context->CSSetShaderResources(0, 6, NullSRV);*/

				Context->Flush();
			}

			void Dispatch(UINT _ThreadGroupCountX, UINT _ThreadGroupCountY, UINT _ThreadGroupCountZ)
			{
				Context->Dispatch(_ThreadGroupCountX, _ThreadGroupCountY, _ThreadGroupCountZ);
			}

		private:
			ComPtr<ID3D11ComputeShader> ComputeShader;

			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

