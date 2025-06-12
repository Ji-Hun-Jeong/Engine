#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class RENDERER_API IUnorderedAccessView : public RefCounter
	{
	public:
		IUnorderedAccessView() = default;
		virtual ~IUnorderedAccessView() = default;

	public:
		virtual void CSSetUnorderedAccessViews(UINT _StartSlot) const = 0;
		virtual void UploadBuffer(UINT _Index, const BufferDesc& _BufferDesc) const = 0;
		virtual void DownloadBuffer(UINT _Index, const BufferDesc& _BufferDesc) const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXUnorderedAccessView : public IUnorderedAccessView
		{
		public:
			DXUnorderedAccessView(ComPtr<ID3D11DeviceContext>& _Context, const std::vector<ComPtr<ID3D11Buffer>>& _Buffers
				, const std::vector<ComPtr<ID3D11Buffer>>& _StagingBuffers
				, const std::vector<ComPtr<ID3D11UnorderedAccessView>>& _UnorderedAccessViews)
				: Context(_Context), UnorderedAccessViews{}
			{
				Buffers.reserve(_Buffers.size());
				for (auto& Buffer : _Buffers)
				{
					Buffer->AddRef();
					Buffers.push_back(Buffer.Get());
				}

				StagingBuffers.reserve(_StagingBuffers.size());
				for (auto& StagingBuffer : _StagingBuffers)
				{
					StagingBuffer->AddRef();
					StagingBuffers.push_back(StagingBuffer.Get());
				}

				UnorderedAccessViews.reserve(_UnorderedAccessViews.size());
				for (auto& UAV : _UnorderedAccessViews)
				{
					UAV->AddRef();
					UnorderedAccessViews.push_back(UAV.Get());
				}
			}
			~DXUnorderedAccessView()
			{
				for (auto& Buffer : Buffers)
					Buffer->Release();
				for (auto& StagingBuffer : StagingBuffers)
					StagingBuffer->Release();
				for (auto& UAV : UnorderedAccessViews)
					UAV->Release();
			}

		public:
			void CSSetUnorderedAccessViews(UINT _StartSlot) const override
			{
				Context->CSSetUnorderedAccessViews(_StartSlot, UnorderedAccessViews.size(), UnorderedAccessViews.data(), nullptr);
			}

			void UploadBuffer(UINT _Index, const BufferDesc& _BufferDesc) const override
			{
				ID3D11Buffer* StagingBuffer = StagingBuffers[_Index];
				D3D11_MAPPED_SUBRESOURCE MS;
				Context->Map(StagingBuffer, 0, D3D11_MAP_WRITE, 0, &MS);
				memcpy(MS.pData, _BufferDesc.Data, _BufferDesc.ElementSize * _BufferDesc.NumOfElement);
				Context->Unmap(StagingBuffer, 0);

				ID3D11Buffer* Buffer = Buffers[_Index];
				Context->CopyResource(Buffer, StagingBuffer);

			}

			void DownloadBuffer(UINT _Index, const BufferDesc& _BufferDesc) const override
			{
				ID3D11Buffer* Buffer = Buffers[_Index];
				ID3D11Buffer* StagingBuffer = StagingBuffers[_Index];
				Context->CopyResource(StagingBuffer, Buffer);

				D3D11_MAPPED_SUBRESOURCE MS;
				Context->Map(StagingBuffer, 0, D3D11_MAP_READ, 0, &MS);
				memcpy(_BufferDesc.Data, MS.pData, _BufferDesc.ElementSize * _BufferDesc.NumOfElement);
				Context->Unmap(StagingBuffer, 0);
			}

		private:
			std::vector<ID3D11Buffer*> Buffers;
			std::vector<ID3D11Buffer*> StagingBuffers;	// Gpu -> Cpu�� �о���� ����
			std::vector<ID3D11UnorderedAccessView*> UnorderedAccessViews;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}

