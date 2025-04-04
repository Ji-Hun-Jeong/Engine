#include "pch.h"
#include "DXDevice.h"
#include "DXContext.h"

namespace Graphics
{
    namespace DX
    {
		DXDevice::DXDevice(HWND _WindowHandle)
			: RenderDevice(_WindowHandle)
			, NumOfMultiSamplingLevel(0)
		{

		}

		DXDevice::~DXDevice()
		{
			
		}

		RenderContext* DXDevice::Initalize()
        {
			D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;
			UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
			D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_9_3 };
			D3D_FEATURE_LEVEL outputLevel;
			
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
			swapChainDesc.BufferDesc.Width = ScreenWidth;
			swapChainDesc.BufferDesc.Height = ScreenHeight;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferCount = 2;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.OutputWindow = WindowHandle;
			swapChainDesc.Windowed = TRUE;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			
			ID3D11DeviceContext* Context = nullptr;
			IDXGISwapChain* SwapChain = nullptr;
			HRESULT hr = ::D3D11CreateDeviceAndSwapChain(nullptr, driverType, 0
				, createDeviceFlags, featureLevel, 1
				, D3D11_SDK_VERSION, &swapChainDesc
				, &SwapChain, Device.GetAddressOf()
				, &outputLevel, &Context);
			if (FAILED(hr)) assert(0);
			
			hr = Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
				&NumOfMultiSamplingLevel);
			if (FAILED(hr)) assert(0);

			DXResource::InitResource(Device.Get());
			
			// Texture를 이용해서 리소스를 만들고 난 후 항상 Texture를 Release해주기
			ID3D11Texture2D* Buffer = nullptr;
			hr = SwapChain->GetBuffer(0, IID_PPV_ARGS(&Buffer));
			ID3D11RenderTargetView* RenderTargetView = nullptr;
			if (Buffer)
				hr = Device->CreateRenderTargetView(Buffer, nullptr, &RenderTargetView);
			if (FAILED(hr)) assert(0);

			Buffer->Release();
			DXResource::RenderTargetView[(UINT)eCategoryRTV::BackBuffer] = RenderTargetView;


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
			ID3D11DepthStencilView* DepthStencilView = nullptr;
			if (FAILED(hr)) assert(0);

			hr = Device->CreateDepthStencilView(Buffer, nullptr, &DepthStencilView);
			if (FAILED(hr)) assert(0);
			Buffer->Release();
			DXResource::DepthStencilView[(UINT)eCategoryDSV::BackBuffer] = DepthStencilView;

			D3D11_VIEWPORT& ViewPort = DXResource::ViewPort[(UINT)eCategoryVP::Basic];
			ZeroMemory(&ViewPort, sizeof(D3D11_VIEWPORT));
			ViewPort.TopLeftX = 0;
			ViewPort.TopLeftY = 0;
			ViewPort.Width = static_cast<float>(ScreenWidth);
			ViewPort.Height = static_cast<float>(ScreenHeight);
			ViewPort.MinDepth = 0.0f;
			ViewPort.MaxDepth = 1.0f;

			Context->Release();
			SwapChain->Release();
			return new DX::DXContext(Context, SwapChain);
        }
        void DXDevice::MakeBuffers(const std::string& _Key, std::vector<Vertex>& _Vertices, std::vector<uint32_t>& _Indices)
        {
			DXBuffers* Buffers = new DXBuffers;

			D3D11_BUFFER_DESC BufferDesc;
			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			BufferDesc.ByteWidth = UINT(sizeof(Vertex) * _Vertices.size());
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			BufferDesc.CPUAccessFlags = 0;
			BufferDesc.StructureByteStride = sizeof(Vertex);

			D3D11_SUBRESOURCE_DATA BufferData = { 0 };
			BufferData.pSysMem = _Vertices.data();
			BufferData.SysMemPitch = 0;
			BufferData.SysMemSlicePitch = 0;
			HRESULT hr = Device->CreateBuffer(&BufferDesc, &BufferData, Buffers->VertexBuffer.GetAddressOf());
			if (FAILED(hr)) assert(0);

			_Vertices.clear();

			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 초기화 후 변경X
			BufferDesc.ByteWidth = UINT(sizeof(uint32_t) * _Indices.size());
			BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			BufferDesc.CPUAccessFlags = 0; // 0 if no CPU access is necessary.
			BufferDesc.StructureByteStride = sizeof(uint32_t);

			BufferData.pSysMem = _Indices.data();
			BufferData.SysMemPitch = 0;
			BufferData.SysMemSlicePitch = 0;

			hr = Device->CreateBuffer(&BufferDesc, &BufferData,
				Buffers->IndexBuffer.GetAddressOf());
			if (FAILED(hr)) assert(0);

			_Indices.clear();

			Buffers->Stride = sizeof(Vertex);

			DXResource::DXBuffers.insert(std::make_pair(_Key, Buffers));
        }
    }
}