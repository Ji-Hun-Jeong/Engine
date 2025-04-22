#pragma once

namespace Graphics
{
	class RENDERER_API Renderer
	{
	public:
		Renderer() {}
		~Renderer() {}

	public:
		void BasicRender(class RenderContext* _RenderContext, const Str::FString& _BufferKey, UINT _IndexCount);

	};
}