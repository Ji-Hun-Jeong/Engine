#include "pch.h"
#include "DXDevice.h"
#include "DXContext.h"

namespace Graphics
{
	namespace DX
	{
		DXDevice::DXDevice(HWND _WindowHandle)
			: RenderDevice(_WindowHandle)
			, Resource()
		{

		}

		DXDevice::~DXDevice()
		{

		}

		Graphics::RenderContext* DXDevice::Initalize()
		{
			// DirectX는 리소스를 Com객체로 관리한다.
			// Com객체는 내부적으로 RefCount를 가지고 있고 이 Com객체를 사용할 때 RefCount가 증가한다. 
			// 그래서 반드시 사용한 후에 RefCount를 감소시켜줘야한다.
			// ComPtr은 Com객체를 위한 스마트포인터고 ComPtr이 사라질 때 Release를 호출해서 RefCount를 감소시킨다.

			// &는 이전 리소스의 참조를 없애고 포인터의 주소를 반환한다.
			// GetAddressOf는 그대로 포인터의 주소를 반환한다.

			// 따라서 DirectX의 리소스는 항상 만들고 더이상 그 객체를 사용할 일이 없으면 바로 Release를 호출하여 RefCount를 감소시켜야한다.

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

			ComPtr<ID3D11DeviceContext> Context;
			ComPtr<IDXGISwapChain> SwapChain;
			HRESULT hr = ::D3D11CreateDeviceAndSwapChain(nullptr, driverType, 0
				, createDeviceFlags, featureLevel, 1
				, D3D11_SDK_VERSION, &swapChainDesc
				, SwapChain.GetAddressOf(), Resource.Device.GetAddressOf()
				, &outputLevel, Context.GetAddressOf());
			if (FAILED(hr)) assert(0);


			hr = Resource.Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
				&Resource.NumOfMultiSamplingLevel);
			if (FAILED(hr)) assert(0);

			Resource.Context = Context;
			Resource.SwapChain = SwapChain;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Texture를 이용해서 리소스를 만들고 난 후 항상 Texture를 Release해주기
			ID3D11Texture2D* Buffer;
			hr = SwapChain->GetBuffer(0, IID_PPV_ARGS(&Buffer));
			ComPtr<ID3D11RenderTargetView> RenderTargetView;
			if (Buffer)
				hr = Resource.Device->CreateRenderTargetView(Buffer, nullptr, RenderTargetView.GetAddressOf());
			if (FAILED(hr)) assert(0);
			Buffer->Release();

			Resource.RenderTargetView[(UINT)eCategoryRTV::BackBuffer] = RenderTargetView;

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

			hr = Resource.Device->CreateTexture2D(&DDesc, nullptr, &Buffer);
			ComPtr<ID3D11DepthStencilView> DepthStencilView;
			if (FAILED(hr)) assert(0);

			hr = Resource.Device->CreateDepthStencilView(Buffer, nullptr, DepthStencilView.GetAddressOf());
			if (FAILED(hr)) assert(0);
			Buffer->Release();

			Resource.DepthStencilView[(UINT)eCategoryDSV::BackBuffer] = DepthStencilView;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

			D3D11_VIEWPORT& ViewPort = Resource.ViewPort[(UINT)eCategoryVP::Basic];
			ZeroMemory(&ViewPort, sizeof(D3D11_VIEWPORT));
			ViewPort.TopLeftX = 0;
			ViewPort.TopLeftY = 0;
			ViewPort.Width = static_cast<float>(ScreenWidth);
			ViewPort.Height = static_cast<float>(ScreenHeight);
			ViewPort.MinDepth = 0.0f;
			ViewPort.MaxDepth = 1.0f;

			Resource.Initalize();

			return new DX::DXContext(Resource);
		}

		void DXDevice::MakeGeometryBuffers(const Str::FString& _Key, void* _Data, size_t _VertexSize, size_t _NumOfVertex, std::vector<uint32_t>& _Indices)
		{
			DXBuffers* Buffers = new DXBuffers;

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
			BufferData.pSysMem = _Data;
			BufferData.SysMemPitch = 0;
			BufferData.SysMemSlicePitch = 0;
			HRESULT hr = Resource.Device->CreateBuffer(&BufferDesc, &BufferData, Buffers->VertexBuffer.GetAddressOf());
			if (FAILED(hr)) assert(0);


			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 초기화 후 변경X
			BufferDesc.ByteWidth = UINT(sizeof(uint32_t) * _Indices.size());
			BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			BufferDesc.CPUAccessFlags = 0; // 0 if no CPU access is necessary.
			BufferDesc.StructureByteStride = sizeof(uint32_t);

			BufferData.pSysMem = _Indices.data();
			BufferData.SysMemPitch = 0;
			BufferData.SysMemSlicePitch = 0;

			hr = Resource.Device->CreateBuffer(&BufferDesc, &BufferData,
				Buffers->IndexBuffer.GetAddressOf());
			if (FAILED(hr)) assert(0);

			_Indices.clear();

			Buffers->Stride = _VertexSize;

			Resource.DXBuffers.insert(std::make_pair(_Key, Buffers));
		}
	}
}