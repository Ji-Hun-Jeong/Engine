#pragma once

namespace Graphics
{
	class RenderDevice
	{
	public:
		explicit RenderDevice(HWND _WindowHandle);
		virtual ~RenderDevice() {}
	public:
		virtual class RenderContext* Initalize() = 0;
		virtual void MakeGeometryBuffers(const std::string& _Key, std::vector<Vertex>& _Vertices
			, std::vector<uint32_t>& _Indices) = 0;

	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;
	};
}

