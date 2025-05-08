#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	struct CpuConstData
	{
		void* Data;
		UINT Size;
	};
	class IConstBuffer : public RefCounter
	{
	public:
		IConstBuffer() = default;
		virtual ~IConstBuffer() = default;

	public:
		virtual void VSSetConstBuffers(UINT _StartSlot) const = 0;
		virtual void PSSetConstBuffers(UINT _StartSlot) const = 0;
		virtual void UpdateBuffer() const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXConstBuffer : public IConstBuffer
		{
		public:
			DXConstBuffer(ComPtr<ID3D11DeviceContext>& _Context, const std::vector<ComPtr<ID3D11Buffer>>& _Buffers
				, const std::vector<CpuConstData>& _CpuData)
				: Context(_Context)
				, Buffers{}
				, CpuData(_CpuData)
			{
				for (auto& Buffer : _Buffers)
				{
					Buffer->AddRef();
					Buffers.push_back(Buffer.Get());
				}
			}
			~DXConstBuffer()
			{
				for (auto Buffer : Buffers)
					Buffer->Release();
			}

		public:
			void VSSetConstBuffers(UINT _StartSlot) const override
			{
				Context->VSSetConstantBuffers(_StartSlot, Buffers.size(), Buffers.data());
			}

			void PSSetConstBuffers(UINT _StartSlot) const override
			{
				Context->PSSetConstantBuffers(_StartSlot, Buffers.size(), Buffers.data());
			}

			void UpdateBuffer() const override
			{
				D3D11_MAPPED_SUBRESOURCE Ms;
				ZeroMemory(&Ms, sizeof(Ms));
				for (size_t i = 0; i < Buffers.size(); ++i)
				{
					Context->Map(Buffers[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &Ms);
					memcpy(Ms.pData, CpuData[i].Data, CpuData[i].Size);
					Context->Unmap(Buffers[i], 0);
				}
			}

		private:
			std::vector<ID3D11Buffer*> Buffers;
			std::vector<CpuConstData> CpuData;

			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

