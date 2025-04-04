#include "pch.h"
#include "DXContext.h"
#include "DXResources.h"

namespace Graphics
{
	namespace DX
	{
		DXContext::DXContext(ID3D11DeviceContext* _Context, IDXGISwapChain* _SwapChain)
			: RenderContext()
			, Context(_Context)
			, SwapChain(_SwapChain)
		{
			
		}
		
	}
}
