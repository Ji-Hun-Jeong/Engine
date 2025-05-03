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
		void UpdateGPUBuffer(IModelRegistry& _ModelRegistry) const
		{
			const std::list<RefCounterPtr<IConstBuffer>>& GlobalConstBuffers = _ModelRegistry.GetGlobalConstBuffers();
			const std::list<Model*>& Models = _ModelRegistry.GetModels();

			for (const auto GlobalConstBuffer : GlobalConstBuffers)
				GlobalConstBuffer->UpdateBuffer();

			for (const auto Model : Models)
				Model->UpdateObjectDatas();
			
		}

		virtual void RenderProcess(IModelRegistry& _ModelRegistry) const = 0;
		virtual void Present() const = 0;

	protected:
		void RenderModel(IModelRegistry& _ModelRegistry) const
		{
			std::list<RefCounterPtr<IConstBuffer>>& GlobalConstBuffers = _ModelRegistry.GetGlobalConstBuffers();
			std::list<Model*>& Models = _ModelRegistry.GetModels();

			for (const auto GlobalConstBuffer : GlobalConstBuffers)
			{
				GlobalConstBuffer->VSSetConstBuffers(0);
				GlobalConstBuffer->PSSetConstBuffers(0);
			}

			for (const auto Model : Models)
			{
				Model->RenderModel(0, 2);
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
		void RenderProcess(IModelRegistry& _ModelRegistry) const override
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
		}
		void Present() const override
		{
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


