#include "pch.h"
#include "DXContext.h"
#include "DXResources.h"

namespace Graphics
{
	namespace DX
	{
		DXContext::DXContext(DXResource& _Resource)
			: RenderContext()
			, Resource(_Resource)
		{
		}
	}
}
