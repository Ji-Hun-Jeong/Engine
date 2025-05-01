#pragma once
#include "Renderer/src/Platform/DirectX/DX.h"
#include "Renderer/src/Interface/IRenderTargetView.h"
#include "Renderer/src/Interface/IViewPort.h"
#include "Renderer/src/Interface/IModel.h"
#include "Renderer/src/Interface/IVertexShaderInputLayout.h"
#include "Renderer/src/Interface/IPixelShader.h"
#include "Renderer/src/Interface/ISampler.h"
#include "Renderer/src/Interface/IRasterizerState.h"
#include "Renderer/src/Interface/IDepthStencilState.h"
#include "Renderer/src/Interface/IConstBuffer.h"
#include "Renderer/src/Interface/ITopology.h"
#include "Renderer/src/Interface/IDraw.h"

namespace Graphics
{
	class IDRGenerator
	{
	public:
		IDRGenerator(HWND _WindowHandle)
		: WindowHandle(_WindowHandle)
		{
			RECT r = { 0 };
			::GetWindowRect(WindowHandle, &r);
			ScreenWidth = r.right - r.left;
			ScreenHeight = r.bottom - r.top;
		}
		virtual ~IDRGenerator() = 0 {}

	public:


	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;

	};

}


