#include "pch.h"
#include "DXContext.h"
#include "DXResources.h"

namespace Graphics
{
	namespace DX
	{
		DXContext::DXContext(HWND _WindowHandle)
			: RenderContext(_WindowHandle)
			, NumOfMultiSamplingLevel(0)
		{
			

			D3D11_VIEWPORT& ViewPort = DXResource::ViewPort[(UINT)eCategoryVP::Basic];
			ZeroMemory(&ViewPort, sizeof(D3D11_VIEWPORT));
			ViewPort.TopLeftX = 0;
			ViewPort.TopLeftY = 0;
			ViewPort.Width = static_cast<float>(ScreenWidth);
			ViewPort.Height = static_cast<float>(ScreenHeight);
			ViewPort.MinDepth = 0.0f;
			ViewPort.MaxDepth = 1.0f;
		}
	}
}
