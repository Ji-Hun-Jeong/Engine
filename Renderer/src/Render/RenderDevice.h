#pragma once
#include "Renderer/src/RenderType.h"

namespace Graphics
{
	class RenderDevice
	{
	public:
		explicit RenderDevice(HWND _WindowHandle);
		virtual ~RenderDevice() {}
	public:
		virtual class RenderContext* Initalize() = 0;
		virtual void MakeGeometryBuffers(const Str::FString& _Key, std::vector<Vertex>& _Vertices
			, std::vector<uint32_t>& _Indices) = 0;
		virtual void MakeVSConstBuffer(const Str::FString& _Key, eCategoryVSConst _VSConstType, UINT _ConstDataSize) = 0;
		virtual void MakePSConstBuffer(const Str::FString& _Key, eCategoryPSConst _PSConstType, UINT _ConstDataSize) = 0;

	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;
	};
}

