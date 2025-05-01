#pragma once
#include "Renderer/src/Platform/DirectX/DXRGenerator.h"
#include "Renderer/src/Geometry/Geometry.h"

namespace Graphics
{
	class IGraphicProcess
	{
	public:
		IGraphicProcess() = default;
		virtual ~IGraphicProcess() = default;

	public:
		void UpdateGPUBuffer()
		{
			for (auto& ConstBuffer : ConstBuffers)
				ConstBuffer->UpdateBuffer();
		}
		void AddModel(std::shared_ptr<IModel>& _Model)
		{
			Models.push_back(_Model);
		}
		void AddConstBuffer(std::shared_ptr<IConstBuffer>& _Buffer)
		{
			ConstBuffers.push_back(_Buffer);
		}
		virtual void RenderProcess() = 0;

	protected:
		std::vector<std::shared_ptr<IModel>> Models;
		std::vector<std::shared_ptr<IConstBuffer>> ConstBuffers;

	};

	class BasicRenderProcess : public IGraphicProcess
	{
	public:
		BasicRenderProcess(DX::DXRGenerator& _Generator)
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
		DX::DXRGenerator& Generator;
		std::shared_ptr<IRenderTargetView> RenderTargetView;
		std::shared_ptr<IDepthStencilState> DepthStencilState;
		std::shared_ptr<IRasterizerState> RasterizerState;
		std::shared_ptr<IVertexShader> VertexShader;
		std::shared_ptr<IPixelShader> PixelShader;
		std::shared_ptr<ITopology> Topology;
		std::shared_ptr<IViewPort> ViewPort;
		std::shared_ptr<IDraw> Drawer;
	};
}


