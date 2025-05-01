#include "pch.h"
#include "DXRGenerator.h"

namespace Graphics
{
	namespace DX
	{
		DXRGenerator::DXRGenerator(HWND _WindowHandle)
			: Super(_WindowHandle)
			, NumOfMultiSamplingLevel(0)
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

			HRESULT hr = ::D3D11CreateDeviceAndSwapChain(nullptr, driverType, 0
				, createDeviceFlags, featureLevel, 1
				, D3D11_SDK_VERSION, &swapChainDesc
				, SwapChain.GetAddressOf(), Device.GetAddressOf()
				, &outputLevel, Context.GetAddressOf());
			if (FAILED(hr)) assert(0);


			hr = Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
				&NumOfMultiSamplingLevel);
			if (FAILED(hr)) assert(0);
		}
	}
}