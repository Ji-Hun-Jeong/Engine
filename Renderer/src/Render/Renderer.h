#pragma once

namespace Graphics
{
	class RENDERER_API Renderer
	{
	public:
		Renderer() {}
		~Renderer() {}

	public:
		void BasicRender(class RenderContext* _RenderContext, const std::string& _BufferKey, UINT _IndexCount);

	};
}