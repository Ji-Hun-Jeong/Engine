#pragma once
#include "Renderer/src/RenderType.h"

namespace Graphics
{
	class ConstData
	{
	public:
		virtual UINT SizeOf() const = 0;
	};

	class RenderDevice
	{
	public:
		explicit RenderDevice(HWND _WindowHandle);
		virtual ~RenderDevice() {}
	public:
		virtual class RenderContext* Initalize() = 0;
		virtual void MakeGeometryBuffers(const std::string& _Key, std::vector<Vertex>& _Vertices
			, std::vector<uint32_t>& _Indices) = 0;
		virtual void MakeVSConstBuffer(const std::string& _Key, eCategoryVSConst _VSConstType, const ConstData& _ConstData) = 0;
		virtual void MakePSConstBuffer(const std::string& _Key, eCategoryPSConst _PSConstType, const ConstData& _ConstData) = 0;

	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;
	};
}

