#pragma once
#include "IGraphicProcess.h"

namespace Graphics
{
	class RENDERER_API ImageRenderProcess : public IGraphicProcess
	{
		using Super = IGraphicProcess;
	public:
		ImageRenderProcess(Graphics::IDRGenerator& _Generator)
			: Super(_Generator)
		{
			RenderTargetView = _Generator.GenerateMainRenderTargetView();
			DepthStencilState = _Generator.GenerateBasicDepthStencilState();
			RasterizerState = _Generator.GenerateSolidCWState();
			const std::vector<InputElementDesc> InputElement =
			{
				{eSementicName::Position, eFormat::Vector3, 0, eInputClass::VertexData},
				{eSementicName::UV, eFormat::Vector2, 12, eInputClass::VertexData}
			};
			VertexShader = _Generator.GenerateVertexShaderAndInputLayout("./Renderer/resource/Shader/ColorVS.hlsl"
				, InputElement);
			PixelShader = _Generator.GeneratePixelShader("./Renderer/resource/Shader/ColorPS.hlsl");
			Topology = _Generator.GenerateTopology(eTopology::Triangle);
			ViewPort = _Generator.GenerateMainViewPort();
		}
		~ImageRenderProcess()
		{

		}

	public:
		void BindRenderProcess(IModelRegistry& _ModelRegistry) const override
		{
			const float ClearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
			RenderTargetView->ClearRenderTargetView(0, ClearColor);
			RenderTargetView->ClearDepthStencilView(D3D11_CLEAR_DEPTH, 1.0f, 0);
			DepthStencilState->OMSetDepthStencilState(0);
			RenderTargetView->OMSetRenderTargets();

			Topology->IASetPrimitiveTopology();
			VertexShader->IASetInputLayout();

			VertexShader->VSSetShader();
			RasterizerState->RSSetState();
			ViewPort->RSSetViewPort();
			PixelShader->PSSetShader();

			Super::renderModel(_ModelRegistry);
		}

	private:
		RefCounterPtr<IRenderTargetView> RenderTargetView;
		RefCounterPtr<IDepthStencilState> DepthStencilState;
		RefCounterPtr<IRasterizerState> RasterizerState;
		RefCounterPtr<IVertexShader> VertexShader;
		RefCounterPtr<IPixelShader> PixelShader;
		RefCounterPtr<ITopology> Topology;
		RefCounterPtr<IViewPort> ViewPort;

	};
}

