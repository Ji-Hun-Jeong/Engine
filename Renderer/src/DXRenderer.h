#pragma once
#include "Renderer.h"
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "../include/SimpleMath.h"

namespace Renderer
{
	using Microsoft::WRL::ComPtr;
	using DirectX::SimpleMath::Vector3;
	class RENDERER_API DXRenderer : public IRenderer
	{
	public:
		explicit DXRenderer(HWND _WindowHandle)
			: IRenderer(_WindowHandle)
		{
			D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;
			UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
			D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_0 ,D3D_FEATURE_LEVEL_9_3 };
			D3D_FEATURE_LEVEL outputLevel;


			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
			swapChainDesc.BufferDesc.Width = ScreenWidth;
			swapChainDesc.BufferDesc.Height = ScreenHeight;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferCount = 2;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapChainDesc.BufferUsage = DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.OutputWindow = WindowHandle;
			swapChainDesc.Windowed = TRUE;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;

			HRESULT result = ::D3D11CreateDeviceAndSwapChain(nullptr, driverType, 0
				, createDeviceFlags, featureLevel, 1
				, D3D11_SDK_VERSION, &swapChainDesc
				, SwapChain.GetAddressOf(), Device.GetAddressOf()
				, &outputLevel, Context.GetAddressOf());

			result = Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
				&NumOfMultiSamplingLevel);

			ID3D11Texture2D* Buffer = nullptr;
			result = SwapChain->GetBuffer(0, IID_PPV_ARGS(&Buffer));
			if (Buffer)
				Device->CreateRenderTargetView(Buffer, nullptr, RenderTargetView.GetAddressOf());
			else
				assert(0);

			D3D11_RASTERIZER_DESC RDesc;
			ZeroMemory(&RDesc, sizeof(RDesc));
			RDesc.FillMode = D3D11_FILL_SOLID;	// WireFrame
			RDesc.CullMode = D3D11_CULL_BACK;	// None, Front
			RDesc.FrontCounterClockwise = false;
			RDesc.DepthClipEnable = true;
			RDesc.MultisampleEnable = true;
			result = Device->CreateRasterizerState(&RDesc, RasterizerState.GetAddressOf());

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

			Buffer = nullptr;
			result = Device->CreateTexture2D(&DDesc, nullptr, &Buffer);
			if (result == S_OK)
				result = Device->CreateDepthStencilView(Buffer, nullptr, DepthStencilView.GetAddressOf());

			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
			depthStencilDesc.DepthEnable = true; // false
			depthStencilDesc.DepthWriteMask =
				D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc =
				D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
			result = Device->CreateDepthStencilState(&depthStencilDesc, DepthStencilState.GetAddressOf());

			D3D11_SAMPLER_DESC sampDesc;
			ZeroMemory(&sampDesc, sizeof(sampDesc));
			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampDesc.MinLOD = 0;
			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
			result = Device->CreateSamplerState(&sampDesc, SamplerState.GetAddressOf());

			ZeroMemory(&ViewPort, sizeof(D3D11_VIEWPORT));
			ViewPort.TopLeftX = 0;
			ViewPort.TopLeftY = 0;
			ViewPort.Width = static_cast<float>(ScreenWidth);
			ViewPort.Height = static_cast<float>(ScreenHeight);
			ViewPort.MinDepth = 0.0f;
			ViewPort.MaxDepth = 1.0f; // Note: important for depth buffering

			Context->RSSetViewports(1, &ViewPort);

			std::vector<D3D11_INPUT_ELEMENT_DESC> basicInputElements =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
					D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3,
					D3D11_INPUT_PER_VERTEX_DATA, 0}
			};
			ComPtr<ID3DBlob> shaderBlob;
			ComPtr<ID3DBlob> errorBlob;

			UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
			compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

			HRESULT hr = D3DCompileFromFile(
				L"../Release/Resource/Shader/BasicVS.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
				"vs_5_0", compileFlags, 0, &shaderBlob, &errorBlob);

			result = Device->CreateVertexShader(shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(), NULL,
				&VertexShader);

			result = Device->CreateInputLayout(basicInputElements.data(), UINT(basicInputElements.size()),
				shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(), InputLayout.GetAddressOf());

			hr = D3DCompileFromFile(
				L"../Release/Resource/Shader/BasicPS.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
				"ps_5_0", compileFlags, 0, &shaderBlob, &errorBlob);


			result = Device->CreatePixelShader(shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(), NULL,
				PixelShader.GetAddressOf());

			std::vector<Vertex> Vertices;
			Vertex V;
			V.pos = Vector3(-0.3f, -0.3f, 0.1f);
			V.color = Vector3(1.0f, 0.0f, 0.0f);
			Vertices.push_back(V);
			V.pos = Vector3(0.0f, 0.3f, 0.1f);
			V.color = Vector3(0.0f, 1.0f, 0.0f);
			Vertices.push_back(V);
			V.pos = Vector3(0.3f, -0.3f, 0.1f);
			V.color = Vector3(0.0f, 0.0f, 1.0f);
			Vertices.push_back(V);
			D3D11_BUFFER_DESC BufferDesc;
			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 초기화 후 변경X
			BufferDesc.ByteWidth = UINT(sizeof(Vertex) * Vertices.size());
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			BufferDesc.CPUAccessFlags = 0; // 0 if no CPU access is necessary.
			BufferDesc.StructureByteStride = sizeof(Vertex);

			D3D11_SUBRESOURCE_DATA BufferData = { 0 }; // MS 예제에서 초기화하는 방식
			BufferData.pSysMem = Vertices.data();
			BufferData.SysMemPitch = 0;
			BufferData.SysMemSlicePitch = 0;
			result = Device->CreateBuffer(&BufferDesc, &BufferData, VertexBuffer.GetAddressOf());

			std::vector<uint32_t> Indices = { 0,1,2 };
			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 초기화 후 변경X
			BufferDesc.ByteWidth = UINT(sizeof(uint32_t) * Indices.size());
			BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			BufferDesc.CPUAccessFlags = 0; // 0 if no CPU access is necessary.
			BufferDesc.StructureByteStride = sizeof(uint32_t);

			BufferData.pSysMem = Indices.data();
			BufferData.SysMemPitch = 0;
			BufferData.SysMemSlicePitch = 0;

			result = Device->CreateBuffer(&BufferDesc, &BufferData,
				IndexBuffer.GetAddressOf());

			IndexCount = Indices.size();
		}
		~DXRenderer()
		{
			
		}

	public:
		struct Vertex
		{
			Vector3 pos;
			Vector3 color;
		};
		void Render() override
		{
			Context->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());
			Context->OMSetDepthStencilState(DepthStencilState.Get(), 0);

			UINT stride = sizeof(Vertex);
			UINT offset = 0;
			Context->IASetInputLayout(InputLayout.Get());
			Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			Context->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &stride, &offset);
			Context->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			Context->VSSetShader(VertexShader.Get(), nullptr, 0);

			Context->RSSetState(RasterizerState.Get());
			Context->RSSetViewports(1, &ViewPort);

			Context->PSSetShader(PixelShader.Get(), nullptr, 0);

			Context->DrawIndexed(IndexCount, 0, 0);
		}
		void Present() override
		{
			SwapChain->Present(1, 0);
		}
		void Clear() override
		{
			const float ClearColor[4] = { 0.0f, 0.7f, 1.0f, 1.0f };
			Context->ClearRenderTargetView(RenderTargetView.Get(), ClearColor);
			Context->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
			ID3D11Debug* pDebug = nullptr;
			Device->QueryInterface(IID_PPV_ARGS(&pDebug));
			pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		}
	private:
		ComPtr<ID3D11Device> Device;
		ComPtr<ID3D11DeviceContext> Context;
		ComPtr<IDXGISwapChain> SwapChain;

		ComPtr<ID3D11Buffer> VertexBuffer;
		ComPtr<ID3D11Buffer> IndexBuffer;

		ComPtr<ID3D11VertexShader> VertexShader;
		ComPtr<ID3D11InputLayout> InputLayout;
		ComPtr<ID3D11PixelShader> PixelShader;
		ComPtr<ID3D11SamplerState> SamplerState;

		ComPtr<ID3D11RasterizerState> RasterizerState;
		ComPtr<ID3D11RenderTargetView> RenderTargetView;
		ComPtr<ID3D11DepthStencilState> DepthStencilState;
		ComPtr<ID3D11DepthStencilView> DepthStencilView;

		D3D11_VIEWPORT ViewPort;

		UINT NumOfMultiSamplingLevel;
		UINT IndexCount;
	};
}