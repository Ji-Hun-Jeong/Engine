#pragma once
#include "Platform/DirectX/DXRGenerator.h"
#include "Render/Model.h"

namespace Graphics
{
	class RENDERER_API IGraphicProcess
	{
	public:
		IGraphicProcess(Graphics::IDRGenerator& _Generator, UINT _ModelsConstBufferStartSlot)
			: Presenter(_Generator.GeneratePresenter())
			, ModelsConstBufferStartSlot(_ModelsConstBufferStartSlot)
		{}
		virtual ~IGraphicProcess()
		{}

	public:
		virtual void BindRenderProcess() const = 0;

		void AddModel(std::shared_ptr<Model>& _Model)
		{
			Models.push_back(_Model);
		}

		void Present() const
		{
			Presenter->Present();
		}

	protected:
		void renderModel() const
		{
			for (const auto Model : Models)
				Model->RenderModel(0, ModelsConstBufferStartSlot, 0);
			
		}

	protected:
		std::list<std::shared_ptr<Model>> Models;
		RefCounterPtr<IPresenter> Presenter;

		UINT ModelsConstBufferStartSlot;
	};

	class RENDERER_API BasicRenderProcess : public IGraphicProcess
	{
		using Super = IGraphicProcess;
	public:
		BasicRenderProcess(Graphics::IDRGenerator& _Generator, UINT _ModelsConstBufferStartSlot)
			: Super(_Generator, _ModelsConstBufferStartSlot)
		{
			RenderTargetView = _Generator.GenerateMainRenderTargetView();
			DepthStencilState = _Generator.GenerateBasicDepthStencilState();
			RasterizerState = _Generator.GenerateSolidCWState();
			const std::vector<InputElementDesc> InputElement =
			{
				{eSementicName::Position, eFormat::Vector3, 0, eInputClass::VertexData},
				{eSementicName::Color, eFormat::Vector3, 12, eInputClass::VertexData}
			};
			VertexShader = _Generator.GenerateVertexShaderAndInputLayout("./Renderer/resource/Shader/ColorVS.hlsl"
				, InputElement);
			PixelShader = _Generator.GeneratePixelShader("./Renderer/resource/Shader/ColorPS.hlsl");
			Topology = _Generator.GenerateTopology(eTopology::Triangle);
			ViewPort = _Generator.GenerateMainViewPort();
		}

		~BasicRenderProcess()
		{

		}

	public:
		void BindRenderProcess() const override
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

			Super::renderModel();
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


