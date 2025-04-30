#pragma once
#include "Renderer/src/Render/RenderContext.h"
#include "DXResources.h"

namespace Graphics
{
	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		using DirectX::SimpleMath::Vector3;

		class RENDERER_API DXContext : public Graphics::RenderContext
		{
			using Super = Graphics::RenderContext;
		public:
			DXContext(DXResource& _Resource);
			DXContext(const DXContext&) = delete;
			DXContext(DXContext&&) = delete;
			~DXContext()
			{

			}

		public:
			void ClearRenderTargetView(eCategoryRTV _RenderTargetView, const float* _Color) override
			{
				ID3D11RenderTargetView* RenderTargetView = Resource.RenderTargetView[(UINT)_RenderTargetView].Get();
				Resource.Context->ClearRenderTargetView(RenderTargetView, _Color);
			}
			void ClearDepthStencilView(eCategoryDSV _DepthStnecilView, UINT _Flag, float _Depth, UINT _Stencil) override
			{
				ID3D11DepthStencilView* DepthStencilView = Resource.DepthStencilView[(UINT)_DepthStnecilView].Get();
				Resource.Context->ClearDepthStencilView(DepthStencilView, _Flag, _Depth, _Stencil);
			}
			void OMSetRenderTargets(UINT _NumView, eCategoryRTV* _RenderTargets, eCategoryDSV _DepthStencilView) override
			{
				ID3D11RenderTargetView* RenderTargets[(UINT)eCategoryRTV::End] = { nullptr };
				for (UINT i = 0; i < _NumView; ++i)
					RenderTargets[i] = Resource.RenderTargetView[i].Get();

				ID3D11DepthStencilView* DepthStencilView =
					Resource.DepthStencilView[(UINT)_DepthStencilView].Get();

				Resource.Context->OMSetRenderTargets(_NumView, RenderTargets, DepthStencilView);
			}
			void OMSetDepthStencilState(eCategoryDSS _DepthStencilState, UINT _StencilRef) override
			{
				ID3D11DepthStencilState* DepthStencilState =
					Resource.DepthStencilState[(UINT)_DepthStencilState].Get();

				Resource.Context->OMSetDepthStencilState(DepthStencilState, _StencilRef);
			}
			void IASetInputLayout(eCategoryIL _InputLayout) override
			{
				ID3D11InputLayout* InputLayout = Resource.InputLayout[(UINT)_InputLayout].Get();
				Resource.Context->IASetInputLayout(InputLayout);
			}
			void IASetPrimitiveTopology(eCategoryTopology _PrimitiveTopology) override
			{
				if (_PrimitiveTopology == eCategoryTopology::Triangle)
					Resource.Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			}
			void IASetBuffers(const Str::FString& _Key, UINT _Start, UINT _Count) override
			{
				DXBuffers* Buffers = Resource.DXBuffers.find(_Key)->second;

				static UINT Stride = Buffers->Stride;
				static UINT Offset = 0;

				Resource.Context->IASetVertexBuffers(_Start, _Count, Buffers->VertexBuffer.GetAddressOf(), &Stride, &Offset);
				Resource.Context->IASetIndexBuffer(Buffers->IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			}
			void VSSetShader(eCategoryVS _VertexShader) override
			{
				ID3D11VertexShader* VertexShader = Resource.VertexShader[(UINT)_VertexShader].Get();
				Resource.Context->VSSetShader(VertexShader, nullptr, 0);
			}
			void VSSetConstBuffers(const Str::FString& _Key, UINT _NumConst, eCategoryVSConst* _VSConst) override
			{
				DXBuffers* DXBuffer = Resource.DXBuffers.find(_Key)->second;

				ID3D11Buffer* VSConst[(UINT)eCategoryVSConst::End] = { nullptr };
				for (UINT i = 0; i < _NumConst; ++i)
					VSConst[i] = DXBuffer->VSConstBuffer[(UINT)_VSConst[i]].Get();

				Resource.Context->VSSetConstantBuffers(0, _NumConst, VSConst);
			}
			void RSSetState(eCategoryRS _RasterizerState) override
			{
				ID3D11RasterizerState* RasterizerState = Resource.RasterizerState[(UINT)_RasterizerState].Get();
				Resource.Context->RSSetState(RasterizerState);
			}
			void RSSetViewPort(UINT _NumViewPort, eCategoryVP _ViewPort) override
			{
				D3D11_VIEWPORT& ViewPort = Resource.ViewPort[(UINT)_ViewPort];
				Resource.Context->RSSetViewports(_NumViewPort, &ViewPort);
			}
			void PSSetShader(eCategoryPS _PixelShader) override
			{
				ID3D11PixelShader* PixelShader = Resource.PixelShader[(UINT)_PixelShader].Get();
				Resource.Context->PSSetShader(PixelShader, nullptr, 0);
			}

			void UpdateVSConstBuffer(const Str::FString& _Key, eCategoryVSConst _VSConst, void* _ConstData
				, UINT _Size) override
			{
				DXBuffers* DXBuffer = Resource.DXBuffers.find(_Key)->second;

				D3D11_MAPPED_SUBRESOURCE Ms;
				ZeroMemory(&Ms, sizeof(Ms));

				Resource.Context->Map(DXBuffer->VSConstBuffer[(UINT)_VSConst].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Ms);
				memcpy(Ms.pData, _ConstData, _Size);
				Resource.Context->Unmap(DXBuffer->VSConstBuffer[(UINT)_VSConst].Get(), 0);
			}

			void PSSetConstBuffers(const Str::FString& _Key, UINT _NumConst, eCategoryPSConst* _PSConst) override
			{
				DXBuffers* DXBuffer = Resource.DXBuffers.find(_Key)->second;
				ID3D11Buffer* PSConst[(UINT)eCategoryPSConst::End] = { nullptr };
				for (UINT i = 0; i < _NumConst; ++i)
					PSConst[i] = DXBuffer->VSConstBuffer[(UINT)_PSConst[i]].Get();
				Resource.Context->PSSetConstantBuffers(0, _NumConst, PSConst);
			}

			void PSSetShaderResources(const std::vector<Str::FString>& _SRVKey)
			{
				std::vector<ID3D11ShaderResourceView*> SRV(_SRVKey.size(), nullptr);
				auto Iter = Resource.Images.begin();
				for (size_t i = 0; i < _SRVKey.size(); ++i)
				{
					Iter = Resource.Images.find(_SRVKey[i]);
					SRV[i] = Iter->second.Get();
				}
				Resource.Context->PSSetShaderResources(0, SRV.size(), SRV.data());
			}

			void DrawIndexed(UINT _IndexCount) override
			{
				Resource.Context->DrawIndexed(_IndexCount, 0, 0);
			}
			void Present() override
			{
				Resource.SwapChain->Present(1, 0);
			}

			void DestoryBuffers(const std::string& _Key) {}

		private:
			DXResource& Resource;

		};
	}
}

