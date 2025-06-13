#pragma once
#include "IGraphicProcess.h"

namespace Graphics
{
	class RENDERER_API ImageRenderProcess : public IGraphicProcess
	{
		using Super = IGraphicProcess;
	public:
		ImageRenderProcess(Graphics::IDRGenerator& _Generator, UINT _ModelsConstBufferStartSlot)
			: Super(_Generator, _ModelsConstBufferStartSlot)
		{
			const float Factor = 1.0f;
			const float BlendFactor[4] = { Factor, Factor, Factor, 1.0f };
			BlendState = _Generator.GenerateBlendState(BlendFactor);
			RenderTargetView = _Generator.GenerateMainRenderTargetView();
			DepthStencilState = _Generator.GenerateBasicDepthStencilState();
			RasterizerState = _Generator.GenerateSolidCWState();
			
			Sampler = _Generator.GenerateSampler();
			ViewPort = _Generator.GenerateMainViewPort();
		}
		~ImageRenderProcess()
		{

		}

	public:
		void InitRenderProcess() const override
		{
			Sampler->VSSetSampler(0);
			Sampler->PSSetSampler(0);
			RasterizerState->RSSetState();
			ViewPort->RSSetViewPort();
		}
		void BindRenderProcess() const override
		{
			const float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			RenderTargetView->ClearRenderTargetView(0, ClearColor);
			RenderTargetView->ClearDepthStencilView(D3D11_CLEAR_DEPTH, 1.0f, 0);

			DepthStencilState->OMSetDepthStencilState(0);
			RenderTargetView->OMSetRenderTargets();
			BlendState->OMSetBlendState();

			Super::renderModel();
		}

	private:
		RefCounterPtr<IRenderTargetView> RenderTargetView;
		RefCounterPtr<IDepthStencilState> DepthStencilState;
		RefCounterPtr<IRasterizerState> RasterizerState;

		RefCounterPtr<ISampler> Sampler;

		RefCounterPtr<IViewPort> ViewPort;
		RefCounterPtr<IBlendState> BlendState;

	};
}

