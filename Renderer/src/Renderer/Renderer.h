#pragma once

namespace Graphics
{
	class RENDERER_API Renderer
	{
	public:
		Renderer() {}
		~Renderer() {}

	public:
		void Render(class RenderContext* _RenderContext);
		void Present() 
		{
		}
		void Clear() 
		{
		}
	private:


	};
}