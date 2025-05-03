#pragma once
#include "DX.h"
#include "Renderer/src/Render/IDRGenerator.h"

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
			RefCounterPtr<IRenderTargetView> GenerateMainRenderTargetView() override
			{
				ID3D11Texture2D* Buffer;
				HRESULT hr = SwapChain->GetBuffer(0, IID_PPV_ARGS(&Buffer));
				ComPtr<ID3D11RenderTargetView> RenderTargetView;
				if (Buffer)
					hr = Device->CreateRenderTargetView(Buffer, nullptr, RenderTargetView.GetAddressOf());
				if (FAILED(hr)) assert(0);
				Buffer->Release();

				D3D11_TEXTURE2D_DESC DDesc;
				ZeroMemory(&DDesc, sizeof(DDesc));
				DDesc.Width = ScreenWidth;
				DDesc.Height = ScreenHeight;
				DDesc.MipLevels = 1;
				DDesc.ArraySize = 1;
				DDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				DDesc.SampleDesc.Count = 1; // how many multisamples
				DDesc.SampleDesc.Quality = 0;
				DDesc.Usage = D3D11_USAGE_DEFAULT;
				DDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				DDesc.CPUAccessFlags = 0;
				DDesc.MiscFlags = 0;

				hr = Device->CreateTexture2D(&DDesc, nullptr, &Buffer);
				ComPtr<ID3D11DepthStencilView> DepthStencilView;
				if (FAILED(hr)) assert(0);

				hr = Device->CreateDepthStencilView(Buffer, nullptr, DepthStencilView.GetAddressOf());
				if (FAILED(hr)) assert(0);
				Buffer->Release();

				std::vector<ComPtr<ID3D11RenderTargetView>> RenderTargetViews{ RenderTargetView };
				return MakeRefCounter<DXRenderTargetView>(Context, RenderTargetViews, DepthStencilView);
			}

			RefCounterPtr<IViewPort> GenerateMainViewPort() override
			{
				D3D11_VIEWPORT ViewPort;
				ZeroMemory(&ViewPort, sizeof(D3D11_VIEWPORT));
				ViewPort.TopLeftX = 0;
				ViewPort.TopLeftY = 0;
				ViewPort.Width = static_cast<float>(ScreenWidth);
				ViewPort.Height = static_cast<float>(ScreenHeight);
				ViewPort.MinDepth = 0.0f;
				ViewPort.MaxDepth = 1.0f;
				std::vector<D3D11_VIEWPORT> ViewPorts{ ViewPort };
				return MakeRefCounter<DXViewPort>(Context, ViewPorts);
			}

			RefCounterPtr<IMesh> GenerateModel(void* _VertexData, size_t _VertexSize, size_t _NumOfVertex
				, void* _IndexData, size_t _IndexSize, size_t _NumOfIndex) override
			{
				D3D11_BUFFER_DESC BufferDesc;
				ZeroMemory(&BufferDesc, sizeof(BufferDesc));
				BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
				BufferDesc.ByteWidth = UINT(_VertexSize * _NumOfVertex);
				BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				BufferDesc.CPUAccessFlags = 0;
				BufferDesc.StructureByteStride = 0;

				// 딱 데이터를 한번만 전달할 때 사용
				// map을 사용할 때는 필요없음
				D3D11_SUBRESOURCE_DATA BufferData = { 0 };
				BufferData.pSysMem = _VertexData;
				BufferData.SysMemPitch = 0;
				BufferData.SysMemSlicePitch = 0;

				ComPtr<ID3D11Buffer> VertexBuffer;
				HRESULT hr = Device->CreateBuffer(&BufferDesc, &BufferData, VertexBuffer.GetAddressOf());
				if (FAILED(hr)) assert(0);


				ZeroMemory(&BufferDesc, sizeof(BufferDesc));
				BufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 초기화 후 변경X
				BufferDesc.ByteWidth = UINT(_IndexSize * _NumOfIndex);
				BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				BufferDesc.CPUAccessFlags = 0; // 0 if no CPU access is necessary.
				BufferDesc.StructureByteStride = 0;

				BufferData.pSysMem = _IndexData;
				BufferData.SysMemPitch = 0;
				BufferData.SysMemSlicePitch = 0;

				ComPtr<ID3D11Buffer> IndexBuffer;
				hr = Device->CreateBuffer(&BufferDesc, &BufferData,
					IndexBuffer.GetAddressOf());
				if (FAILED(hr)) assert(0);

				DXGI_FORMAT Format;
				switch (_IndexSize)
				{
				case 1:
					Format = DXGI_FORMAT_R8_UINT;
					break;
				case 2:
					Format = DXGI_FORMAT_R16_UINT;
					break;
				case 4:
					Format = DXGI_FORMAT_R32_UINT;
					break;
				}

				std::vector<ComPtr<ID3D11Buffer>> VertexBuffers{ VertexBuffer };
				return MakeRefCounter<DXModel>(Context, VertexBuffers, IndexBuffer, Format, _VertexSize, 0, _NumOfIndex);
			}

			RefCounterPtr<IConstBuffer> GenerateConstBuffer(const std::vector<CpuConstData>& _CpuData) override
			{
				std::vector<ComPtr<ID3D11Buffer>> Buffers;

				Buffers.reserve(_CpuData.size());
				for (size_t i = 0; i < _CpuData.size(); ++i)
				{
					D3D11_BUFFER_DESC BufferDesc;
					ZeroMemory(&BufferDesc, sizeof(BufferDesc));
					BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
					BufferDesc.ByteWidth = _CpuData[i].Size;
					BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
					BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					BufferDesc.StructureByteStride = 0;

					ComPtr<ID3D11Buffer> Buffer;
					HRESULT hr = Device->CreateBuffer(&BufferDesc, nullptr, Buffer.GetAddressOf());
					if (FAILED(hr)) assert(0);
					Buffers.push_back(Buffer);
				}
				return MakeRefCounter<DXConstBuffer>(Context, Buffers, _CpuData);
			}

			RefCounterPtr<IVertexShader> GenerateVertexShaderAndInputLayout(const Str::FString& _Path
				, const std::vector<InputElementDesc>& _InputElements) override
			{
				ComPtr<ID3DBlob> shaderBlob;
				ComPtr<ID3DBlob> errorBlob;

				UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
				compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
				const std::wstring WStr = _Path.GetWString();

				HRESULT hr = D3DCompileFromFile(
					WStr.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
					"vs_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf());
				if (FAILED(hr))	assert(0);

				ComPtr<ID3D11VertexShader> VertexShader;
				hr = Device->CreateVertexShader(shaderBlob->GetBufferPointer(),
					shaderBlob->GetBufferSize(), NULL,
					VertexShader.GetAddressOf());
				if (FAILED(hr))	assert(0);

				std::vector<D3D11_INPUT_ELEMENT_DESC> basicInputElements;
				for (auto IED : _InputElements)
				{
					D3D11_INPUT_ELEMENT_DESC Desc;
					ZeroMemory(&Desc, sizeof(Desc));
					switch (IED.SementicName)
					{
					case eSementicName::Position:
						Desc.SemanticName = "POSITION";
						break;
					case eSementicName::Color:
						Desc.SemanticName = "COLOR";
						break;
					default:
						return nullptr;
					}
					switch (IED.Format)
					{
					case eFormat::Vector3:
						Desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
						break;
					default:
						return nullptr;
					}
					Desc.AlignedByteOffset = IED.Offset;
					switch (IED.InputClass)
					{
					case eInputClass::VertexData:
						Desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						break;
					default:
						return nullptr;
					}
					basicInputElements.push_back(Desc);
				}

				ComPtr<ID3D11InputLayout> InputLayout;
				hr = Device->CreateInputLayout(basicInputElements.data(), UINT(basicInputElements.size()),
					shaderBlob->GetBufferPointer(),
					shaderBlob->GetBufferSize(), InputLayout.GetAddressOf());
				if (FAILED(hr))	assert(0);

				return MakeRefCounter<DXVertexShader>(Context, VertexShader, InputLayout);
			}

			RefCounterPtr<IPixelShader> GeneratePixelShader(const Str::FString& _Path) override
			{
				ComPtr<ID3DBlob> shaderBlob;
				ComPtr<ID3DBlob> errorBlob;

				UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
				compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
				const std::wstring Wstr = _Path.GetWString();
				HRESULT hr = D3DCompileFromFile(
					Wstr.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
					"ps_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf());
				if (FAILED(hr))	assert(0);

				ComPtr<ID3D11PixelShader> PixelShader;
				hr = Device->CreatePixelShader(shaderBlob->GetBufferPointer(),
					shaderBlob->GetBufferSize(), NULL,
					PixelShader.GetAddressOf());
				if (FAILED(hr))	assert(0);
				return MakeRefCounter<DXPixelShader>(Context, PixelShader);
			}

			RefCounterPtr<ISampler> GenerateLinearSampler() override
			{
				D3D11_SAMPLER_DESC sampDesc;
				ZeroMemory(&sampDesc, sizeof(sampDesc));
				sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
				sampDesc.MinLOD = 0;
				sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

				ComPtr<ID3D11SamplerState> SamplerState;
				HRESULT hr = Device->CreateSamplerState(&sampDesc, SamplerState.GetAddressOf());
				if (FAILED(hr))
					assert(0);

				std::vector<ComPtr<ID3D11SamplerState>> Samplers{ SamplerState };
				return MakeRefCounter<DXSampler>(Context, Samplers);
			}

			RefCounterPtr<IRasterizerState> GenerateSolidCWState() override
			{
				D3D11_RASTERIZER_DESC RDesc;
				ZeroMemory(&RDesc, sizeof(RDesc));
				RDesc.FillMode = D3D11_FILL_SOLID;	// WireFrame
				RDesc.CullMode = D3D11_CULL_BACK;	// None, Front
				RDesc.FrontCounterClockwise = false;
				RDesc.DepthClipEnable = true;
				RDesc.MultisampleEnable = true;

				ComPtr<ID3D11RasterizerState> RasterizerState;
				HRESULT hr = Device->CreateRasterizerState(&RDesc, RasterizerState.GetAddressOf());
				if (FAILED(hr)) assert(0);

				return MakeRefCounter<DXRasterizerState>(Context, RasterizerState);
			}

			RefCounterPtr<IDepthStencilState> GenerateBasicDepthStencilState() override
			{
				D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
				ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
				depthStencilDesc.DepthEnable = true; // false
				depthStencilDesc.DepthWriteMask =
					D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
				depthStencilDesc.DepthFunc =
					D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

				ComPtr<ID3D11DepthStencilState> DepthStencilState;
				HRESULT hr = Device->CreateDepthStencilState(&depthStencilDesc, DepthStencilState.GetAddressOf());
				if (FAILED(hr)) assert(0);

				return MakeRefCounter<DXDepthStencilState>(Context, DepthStencilState);
			}

			RefCounterPtr<ITopology> GenerateTopology(eTopology _Topology) override
			{
				D3D11_PRIMITIVE_TOPOLOGY Topology;
				switch (_Topology)
				{
				case eTopology::Triangle:
					Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					break;
				default:
					return nullptr;
				}
				return MakeRefCounter<DXTopology>(Context, Topology);
			}

			RefCounterPtr<IDraw> GenerateDrawer() override
			{
				return MakeRefCounter<DXDraw>(Context, SwapChain);
			}
		private:
			ComPtr<ID3D11Device> Device;
			ComPtr<ID3D11DeviceContext> Context;
			ComPtr<IDXGISwapChain> SwapChain;
			UINT NumOfMultiSamplingLevel;
		};
	}
}


