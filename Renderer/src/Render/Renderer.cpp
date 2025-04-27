#include "pch.h"
#include "Renderer.h"
#include "RenderContext.h"
#include "RenderType.h"

namespace Graphics
{
    void Renderer::ColorRender(RenderContext* _RenderContext, const Str::FString& _BufferKey, UINT _IndexCount)
    {
        _RenderContext->IASetInputLayout(eCategoryIL::Basic);
        _RenderContext->IASetPrimitiveTopology(eCategoryTopology::Triangle);
        _RenderContext->IASetBuffers(_BufferKey, 0, 1);

        eCategoryVSConst BasicConst = eCategoryVSConst::Basic;
        _RenderContext->VSSetShader(eCategoryVS::Color);
        _RenderContext->VSSetConstBuffers(_BufferKey, 1, &BasicConst);

        _RenderContext->RSSetState(eCategoryRS::SolidCw);
        _RenderContext->RSSetViewPort(1, eCategoryVP::Basic);

        _RenderContext->PSSetShader(eCategoryPS::Color);

        _RenderContext->DrawIndexed(_IndexCount);
    }
    void Renderer::ImageRender(RenderContext* _RenderContext, const Str::FString& _BufferKey
        , const std::vector<Str::FString>& _SRVKey, UINT _IndexCount)
    {
        _RenderContext->IASetInputLayout(eCategoryIL::Basic);
        _RenderContext->IASetPrimitiveTopology(eCategoryTopology::Triangle);
        _RenderContext->IASetBuffers(_BufferKey, 0, 1);

        eCategoryVSConst BasicConst = eCategoryVSConst::Basic;
        _RenderContext->VSSetShader(eCategoryVS::Color);
        _RenderContext->VSSetConstBuffers(_BufferKey, 1, &BasicConst);

        _RenderContext->RSSetState(eCategoryRS::SolidCw);
        _RenderContext->RSSetViewPort(1, eCategoryVP::Basic);

        _RenderContext->PSSetShader(eCategoryPS::Color);
        _RenderContext->PSSetShaderResources(_SRVKey);

        _RenderContext->DrawIndexed(_IndexCount);
    }
}