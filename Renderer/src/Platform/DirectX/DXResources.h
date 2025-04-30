#pragma once
#include "DX.h"
#include "Renderer/src/RenderType.h"

namespace Graphics
{
	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		struct DXBuffers
		{
			ComPtr<ID3D11Buffer> VertexBuffer;
			ComPtr<ID3D11Buffer> IndexBuffer;
			ComPtr<ID3D11Buffer> VSConstBuffer[(UINT)eCategoryVSConst::End];
			ComPtr<ID3D11Buffer> PSConstBuffer[(UINT)eCategoryPSConst::End];
			UINT Stride = 0;
		};
		class DXResource
		{
			friend class DXDevice;
			friend class DXContext;
			friend class DXModel;
		public:
			DXResource();
			~DXResource();

		public:
			void Initalize();
			void InitShader();
			void InitSampler();
			void InitRS();
			void InitDSS();

		private:
			ComPtr<ID3D11VertexShader> VertexShader[(UINT)eCategoryVS::End];
			ComPtr<ID3D11InputLayout> InputLayout[(UINT)eCategoryIL::End];
			ComPtr<ID3D11PixelShader> PixelShader[(UINT)eCategoryPS::End];
			ComPtr<ID3D11SamplerState> SamplerState[(UINT)eCategorySS::End];

			D3D11_VIEWPORT ViewPort[(UINT)eCategoryVP::End];
			ComPtr<ID3D11RasterizerState> RasterizerState[(UINT)eCategoryRS::End];
			ComPtr<ID3D11DepthStencilState> DepthStencilState[(UINT)eCategoryDSS::End];
			ComPtr<ID3D11DepthStencilView> DepthStencilView[(UINT)eCategoryDSV::End];
			ComPtr<ID3D11RenderTargetView> RenderTargetView[(UINT)eCategoryRTV::End];

			std::unordered_map<Str::FString, struct DXBuffers*> DXBuffers;
			std::unordered_map<Str::FString, ComPtr<ID3D11ShaderResourceView>> Images;

			ComPtr<ID3D11Device> Device;
			ComPtr<ID3D11DeviceContext> Context;
			ComPtr<IDXGISwapChain> SwapChain;
			UINT NumOfMultiSamplingLevel;
		};
	}
}


