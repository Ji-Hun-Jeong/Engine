#pragma once
#include "Renderer/src/Platform/DirectX/DXRGenerator.h"
#include "Renderer/src/Render/ModelRegistry.h"

namespace Graphics
{
	class RENDERER_API IGraphicProcess
	{
	public:
		IGraphicProcess() = default;
		virtual ~IGraphicProcess()
		{

		}

	public:
		void UpdateGPUBuffer(IModelRegistry& _ModelRegistry)
		{
			std::list<IConstBuffer*>& ConstBuffers = _ModelRegistry.GetConstBuffers();
			for (auto ConstBuffer : ConstBuffers)
				ConstBuffer->UpdateBuffer();
		}

		virtual void RenderProcess(IModelRegistry& _ModelRegistry) = 0;

	protected:
		void RenderModel(IModelRegistry& _ModelRegistry)
		{
			std::list<IConstBuffer*>& ConstBuffers = _ModelRegistry.GetConstBuffers();
			std::list<IModel*>& Models = _ModelRegistry.GetModels();

			for (auto ConstBuffer : ConstBuffers)
				ConstBuffer->VSSetConstBuffers(0);

			for (auto Model : Models)
			{
				Model->IASetBuffer(0);
				Model->DrawIndexed();
			}
		}

	};

	class RENDERER_API BasicRenderProcess : public IGraphicProcess
	{
		using Super = IGraphicProcess;
	public:
		BasicRenderProcess(Graphics::IDRGenerator& _Generator)
			: Super()
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

			Drawer = _Generator.GenerateDrawer();

		}
		~BasicRenderProcess()
		{

		}

	public:
		void RenderProcess(IModelRegistry& _ModelRegistry) override
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

			Super::RenderModel(_ModelRegistry);

			Drawer->Present();
		}

	private:
		RefCounterPtr<IRenderTargetView> RenderTargetView;
		RefCounterPtr<IDepthStencilState> DepthStencilState;
		RefCounterPtr<IRasterizerState> RasterizerState;
		RefCounterPtr<IVertexShader> VertexShader;
		RefCounterPtr<IPixelShader> PixelShader;
		RefCounterPtr<ITopology> Topology;
		RefCounterPtr<IViewPort> ViewPort;
		RefCounterPtr<IDraw> Drawer;

	};
}


