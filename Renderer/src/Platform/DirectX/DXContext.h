#pragma once
#include "Renderer/RenderContext.h"
#include "DXResources.h"

namespace Graphics
{
	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		using DirectX::SimpleMath::Vector3;

		class RENDERER_API DXContext : public Graphics::RenderContext
		{
			using Super = RenderContext;
		public:
			DXContext(ID3D11DeviceContext* _Context, IDXGISwapChain* _SwapChain);
			DXContext(const DXContext&) = delete;
			DXContext(DXContext&&) = delete;
			~DXContext()
			{
				DXResource::DestroyResource();
			}

		public:
			void ClearRenderTargetView(eCategoryRTV _RenderTargetView, const float* _Color) override
			{
				ID3D11RenderTargetView* RenderTargetView = DXResource::RenderTargetView[(UINT)_RenderTargetView].Get();
				Context->ClearRenderTargetView(RenderTargetView, _Color);
			}
			void ClearDepthStencilView(eCategoryDSV _DepthStnecilView, UINT _Flag, float _Depth, UINT _Stencil) override
			{
				ID3D11DepthStencilView* DepthStencilView = DXResource::DepthStencilView[(UINT)_DepthStnecilView].Get();
				Context->ClearDepthStencilView(DepthStencilView, _Flag, _Depth, _Stencil);
			}
			void OMSetRenderTargets(UINT _NumView, eCategoryRTV* _RenderTargets, eCategoryDSV _DepthStencilView) override
			{
				ID3D11RenderTargetView* RenderTargets[(UINT)eCategoryRTV::End] = { nullptr };
				for (UINT i = 0; i < _NumView; ++i)
					RenderTargets[i] = DXResource::RenderTargetView[i].Get();

				ID3D11DepthStencilView* DepthStencilView =
					DXResource::DepthStencilView[(UINT)_DepthStencilView].Get();

				Context->OMSetRenderTargets(_NumView, RenderTargets, DepthStencilView);
			}
			void OMSetDepthStencilState(eCategoryDSS _DepthStencilState, UINT _StencilRef) override
			{
				ID3D11DepthStencilState* DepthStencilState =
					DXResource::DepthStencilState[(UINT)_DepthStencilState].Get();

				Context->OMSetDepthStencilState(DepthStencilState, _StencilRef);
			}
			void IASetInputLayout(eCategoryIL _InputLayout) override
			{
				ID3D11InputLayout* InputLayout = DXResource::InputLayout[(UINT)_InputLayout].Get();
				Context->IASetInputLayout(InputLayout);
			}
			void IASetPrimitiveTopology(eCategoryTopology _PrimitiveTopology) override
			{
				if (_PrimitiveTopology == eCategoryTopology::Triangle)
					Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			}
			void IASetBuffers(UINT _Start, UINT _Count, const std::string& _Key) override
			{
				DXBuffers* Buffers = DXResource::DXBuffers.find(_Key)->second;

				static UINT Stride = Buffers->Stride;
				static UINT Offset = 0;

				Context->IASetVertexBuffers(_Start, _Count, Buffers->VertexBuffer.GetAddressOf(), &Stride, &Offset);
				Context->IASetIndexBuffer(Buffers->IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			}
			void VSSetShader(eCategoryVS _VertexShader) override
			{
				ID3D11VertexShader* VertexShader = DXResource::VertexShader[(UINT)_VertexShader].Get();
				Context->VSSetShader(VertexShader, nullptr, 0);
			}
			void RSSetState(eCategoryRS _RasterizerState) override
			{
				ID3D11RasterizerState* RasterizerState = DXResource::RasterizerState[(UINT)_RasterizerState].Get();
				Context->RSSetState(RasterizerState);
			}
			void RSSetViewPort(UINT _NumViewPort, eCategoryVP _ViewPort) override
			{
				D3D11_VIEWPORT& ViewPort = DXResource::ViewPort[(UINT)_ViewPort];
				Context->RSSetViewports(_NumViewPort, &ViewPort);
			}
			void PSSetShader(eCategoryPS _PixelShader) override
			{
				ID3D11PixelShader* PixelShader = DXResource::PixelShader[(UINT)_PixelShader].Get();
				Context->PSSetShader(PixelShader, nullptr, 0);
			}
			void DrawIndexed(UINT _IndexCount) override
			{
				Context->DrawIndexed(_IndexCount, 0, 0);
			}
			void Present() override
			{
				SwapChain->Present(1, 0);
			}

			void DestoryBuffers(const std::string& _Key) {}

		private:
			ComPtr<ID3D11DeviceContext> Context;
			ComPtr<IDXGISwapChain> SwapChain;

		};
	}
}