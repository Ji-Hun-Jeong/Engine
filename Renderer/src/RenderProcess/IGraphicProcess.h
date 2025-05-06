#pragma once
#include "Renderer/src/Platform/DirectX/DXRGenerator.h"
#include "Renderer/src/Render/IModelRegistry.h"

namespace Graphics
{
	class RENDERER_API IGraphicProcess
	{
	public:
		IGraphicProcess(Graphics::IDRGenerator& _Generator)
			: Presenter(_Generator.GeneratePresenter())
		{}
		virtual ~IGraphicProcess()
		{}

	public:
		virtual void BindRenderProcess(IModelRegistry& _ModelRegistry) const = 0;

		void Present() const
		{
			Presenter->Present();
		}

		void UpdateGPUBuffer(IModelRegistry& _ModelRegistry) const
		{
			const std::list<IConstBuffer*>& GlobalConstBuffers = _ModelRegistry.GetGlobalConstBuffers();
			const std::list<std::shared_ptr<Model>>& Models = _ModelRegistry.GetModels();

			for (const auto GlobalConstBuffer : GlobalConstBuffers)
				GlobalConstBuffer->UpdateBuffer();

			for (const auto Model : Models)
				Model->UpdateObjectDatas();
			
		}

	protected:
		void renderModel(IModelRegistry& _ModelRegistry) const
		{
			std::list<IConstBuffer*>& GlobalConstBuffers = _ModelRegistry.GetGlobalConstBuffers();
			std::list<std::shared_ptr<Model>>& Models = _ModelRegistry.GetModels();

			for (const auto GlobalConstBuffer : GlobalConstBuffers)
			{
				GlobalConstBuffer->VSSetConstBuffers(0);
				GlobalConstBuffer->PSSetConstBuffers(0);
			}

			for (const auto Model : Models)
				Model->RenderModel(0, 2, 0);
			
		}

	protected:
		RefCounterPtr<IPresenter> Presenter;

	};

	class RENDERER_API BasicRenderProcess : public IGraphicProcess
	{
		using Super = IGraphicProcess;
	public:
		BasicRenderProcess(Graphics::IDRGenerator& _Generator)
			: Super(_Generator)
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


