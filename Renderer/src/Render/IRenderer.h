#pragma once
#include "Renderer/src/Platform/DirectX/DXRGenerator.h"
#include "Renderer/src/Geometry/Geometry.h"

namespace Graphics
{
	class IGraphicProcess
	{
	public:
		IGraphicProcess() = default;
		virtual ~IGraphicProcess()
		{

		}

	public:
		void UpdateGPUBuffer()
		{
			for (auto& ConstBuffer : ConstBuffers)
				ConstBuffer->UpdateBuffer();
		}
		void AddModel(RefCounterPtr<IModel>& _Model)
		{
			Models.push_back(_Model);
		}
		void AddConstBuffer(RefCounterPtr<IConstBuffer>& _Buffer)
		{
			ConstBuffers.push_back(_Buffer);
		}
		virtual void RenderProcess() = 0;

	protected:
		// Interface객체 참조카운트 관리할 수 있는 부모 클래스 만들기
		std::vector<RefCounterPtr<IModel>> Models;
		std::vector<RefCounterPtr<IConstBuffer>> ConstBuffers;

	};

	class BasicRenderProcess : public IGraphicProcess
	{
	public:
		BasicRenderProcess(Graphics::IDRGenerator& _Generator)
			: Generator(_Generator)
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
			auto MeshData = Geometry::GenerateColorTriangle();
			auto Model = Generator.GenerateModel(MeshData.Vertices.data(), sizeof(ColorVertex), MeshData.Vertices.size()
				, MeshData.Indices.data(), sizeof(uint32_t), MeshData.Indices.size());
			AddModel(Model);

			using namespace DirectX::SimpleMath;
			Matrix* Matrix = new DirectX::SimpleMath::Matrix;
			*Matrix = Matrix::CreateScale(1.0f).Transpose();
			CpuConstData* Data = new CpuConstData;
			Data->Data = Matrix;
			Data->Size = sizeof(*Matrix);
			const std::vector<CpuConstData*> ConstDatas{ Data };
			auto Const = Generator.GenerateConstBuffer(ConstDatas);
			AddConstBuffer(Const);

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

			for (size_t i = 0; i < Models.size(); ++i)
			{
				Models[i]->IASetBuffer(0);
				ConstBuffers[i]->VSSetConstBuffers(0);
				Models[i]->DrawIndexed();
			}

			Drawer->Present();

		}

	private:
		Graphics::IDRGenerator& Generator;
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


