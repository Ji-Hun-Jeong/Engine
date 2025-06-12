#pragma once
#include "DX.h"
#include "Renderer/src/Render/IDRGenerator.h"
#include "Renderer/include/WICTextureLoader.h"

namespace Graphics
{
	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class RENDERER_API DXRGenerator : public IDRGenerator
		{
			using Super = IDRGenerator;
		public:
			DXRGenerator(HWND _WindowHandle);
			~DXRGenerator() = default;

		public:
			RefCounterPtr<IRenderTargetView> GenerateMainRenderTargetView() override;

			RefCounterPtr<IViewPort> GenerateMainViewPort() override;

			RefCounterPtr<IMesh> GenerateMesh(void* _VertexData, size_t _VertexSize, size_t _NumOfVertex
				, void* _IndexData, size_t _IndexSize, size_t _NumOfIndex) override;

			RefCounterPtr<IConstBuffer> GenerateConstBuffer(const std::vector<CpuConstData>& _CpuData) override;

			RefCounterPtr<IVertexShader> GenerateVertexShaderAndInputLayout(const Str::FString& _Path
				, const std::vector<InputElementDesc>& _InputElements) override;

			RefCounterPtr<IPixelShader> GeneratePixelShader(const Str::FString& _Path) override;

			RefCounterPtr<ISampler> GenerateSampler() override;

			RefCounterPtr<IRasterizerState> GenerateSolidCWState() override;

			RefCounterPtr<IDepthStencilState> GenerateBasicDepthStencilState() override;

			RefCounterPtr<ITopology> GenerateTopology(eTopology _Topology) override;

			RefCounterPtr<IPresenter> GeneratePresenter() override
			{
				return MakeRefCounter<DXPresenter>(Context, SwapChain);
			}

			RefCounterPtr<IShaderResource> GenerateShaderResource(const std::vector<Str::FString>& _Paths) override;

			RefCounterPtr<IBlendState> GenerateBlendState(const float* _BlendFactor) override;

			RefCounterPtr<IComputeShader> GenerateComputeShader(const Str::FString& _Path) override;

			RefCounterPtr<IUnorderedAccessView> GenerateUnorderedAccessView(const std::vector<BufferDesc>& _BufferDesc) override;

		private:
			ComPtr<ID3D11Device> Device;
			ComPtr<ID3D11DeviceContext> Context;
			ComPtr<IDXGISwapChain> SwapChain;
			UINT NumOfMultiSamplingLevel;
		};
	}
}


