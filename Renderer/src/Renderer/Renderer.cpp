#include "pch.h"
#include "Renderer.h"
#include "RenderContext.h"

namespace Graphics
{
    void Renderer::BasicRender(RenderContext* _RenderContext, const std::string& _BufferKey, UINT _IndexCount)
    {
        _RenderContext->IASetInputLayout(eCategoryIL::Basic);
        _RenderContext->IASetPrimitiveTopology(eCategoryTopology::Triangle);
        _RenderContext->IASetBuffers(0, 1, _BufferKey);
        _RenderContext->VSSetShader(eCategoryVS::Basic);
        _RenderContext->RSSetState(eCategoryRS::SolidCw);
        _RenderContext->RSSetViewPort(1, eCategoryVP::Basic);
        _RenderContext->PSSetShader(eCategoryPS::Basic);
        _RenderContext->DrawIndexed(_IndexCount);
    }
}