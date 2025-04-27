#pragma once

namespace Graphics
{
	class RENDERER_API Renderer
	{
	public:
		Renderer() {}
		~Renderer() {}

	public:
		void ColorRender(class RenderContext* _RenderContext, const Str::FString& _BufferKey, UINT _IndexCount);
		void ImageRender(class RenderContext* _RenderContext, const Str::FString& _BufferKey
			, const std::vector<Str::FString>& _SRVKey, UINT _IndexCount);

	};
}