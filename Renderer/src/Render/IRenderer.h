#pragma once
#include "Renderer/src/Render/IDRGenerator.h"
#include "Renderer/src/Geometry/Geometry.h"

namespace Graphics
{
	class IGraphicProcess
	{
	public:
		IGraphicProcess(Graphics::IDRGenerator& _Generator)
			: Generator(_Generator)
		{}
		virtual ~IGraphicProcess()
		{

		}

	public:
		void UpdateGPUBuffer()
		{
			auto& ConstBuffers = Generator.GetRegistry().GetConstBuffers();
			for (auto& ConstBuffer : ConstBuffers)
				ConstBuffer->UpdateBuffer();
		}
		void RenderModel()
		{
			auto& Models = Generator.GetRegistry().GetModels();
			auto& ConstBuffers = Generator.GetRegistry().GetConstBuffers();
			for (auto ConstBuffer : ConstBuffers)
				ConstBuffer->VSSetConstBuffers(0);
			for (auto Model : Models)
			{
				Model->IASetBuffer(0);
				Model->DrawIndexed();
			}
		}
		virtual void RenderProcess() = 0;

	protected:
		// Interface객체 참조카운트 관리할 수 있는 부모 클래스 만들기
		Graphics::IDRGenerator& Generator;

	};

	class BasicRenderProcess : public IGraphicProcess
	{
		using Super = IGraphicProcess;
	public:
		BasicRenderProcess(Graphics::IDRGenerator& _Generator)
			: Super(_Generator)
		{
			RenderTargetView = Generator.GenerateMainRenderTargetView();
			DepthStencilState = Generator.GenerateBasicDepthStencilState();
			RasterizerState = Generator.GenerateSolidCWState();
			const std::vector<InputElementDesc> InputElement =
			{
				{eSementicName::Position, eFormat::Vector3, 0, eInputClass::VertexData},
				{eSementicName::Color, eFormat::Vector3, 12, eInputClass::VertexData}
			};
			VertexShader = Generator.GenerateVertexShaderAndInputLayout("./Renderer/resource/Shader/ColorVS.hlsl"
				, InputElement);
			PixelShader = Generator.GeneratePixelShader("./Renderer/resource/Shader/ColorPS.hlsl");
			Topology = Generator.GenerateTopology(eTopology::Triangle);
			ViewPort = Generator.GenerateMainViewPort();

			Drawer = Generator.GenerateDrawer();

		}
		~BasicRenderProcess()
		{

		}

	public:
		void RenderProcess() override
		{
			const float ClearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
			RenderTargetView->ClearRenderTargetView(0, ClearColor);
			RenderTargetView->ClearDepthStencilView(D3D11_CLEAR_DEPTH, 1.0f, 0);
			RenderTargetView->OMSetRenderTargets();
			DepthStencilState->OMSetDepthStencilState(0);

			Topology->IASetPrimitiveTopology();
			VertexShader->IASetInputLayout();

			VertexShader->VSSetShader();
			RasterizerState->RSSetState();
			ViewPort->RSSetViewPort();
			PixelShader->PSSetShader();

			Super::RenderModel();

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


