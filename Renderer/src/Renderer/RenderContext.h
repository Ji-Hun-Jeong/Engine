#pragma once

namespace Graphics
{
	class RENDERER_API RenderContext
	{
	public:
		RenderContext() = default;
		RenderContext(const RenderContext&) = delete;
		virtual ~RenderContext() {}

	public:
		virtual void ClearRenderTargetView(eCategoryRTV _RenderTargetView, const float* _Color) = 0;
		virtual void ClearDepthStencilView(eCategoryDSV _DepthStnecilView, UINT _Flag, float _Depth, UINT _Stencil) = 0;
		virtual void OMSetRenderTargets(UINT _NumView, eCategoryRTV* _RenderTargets, eCategoryDSV _DepthStencilView) = 0;
		virtual void OMSetDepthStencilState(eCategoryDSS _DepthStencilState, UINT _StencilRef) = 0;
		virtual void IASetInputLayout(eCategoryIL _InputLayout) = 0;
		virtual void IASetPrimitiveTopology(eCategoryTopology _PrimitiveTopology) = 0;
		virtual void IASetBuffers(UINT _Start, UINT _Count, const std::string& _Key) = 0;

		virtual void VSSetShader(eCategoryVS _VertexShader) = 0;

		virtual void RSSetState(eCategoryRS _RasterizerState) = 0;
		virtual void RSSetViewPort(UINT _NumViewPort, eCategoryVP _ViewPort) = 0;

		virtual void PSSetShader(eCategoryPS _PixelShader) = 0;

		virtual void DrawIndexed(UINT _IndexCount) = 0;
		
		virtual void Present() = 0;

	protected:


	};
}