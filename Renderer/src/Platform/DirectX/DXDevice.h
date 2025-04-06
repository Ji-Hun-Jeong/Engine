#pragma once
#include "Renderer/src/Render/RenderDevice.h"
#include "DX.h"

namespace Graphics
{
    namespace DX
    {
        using Microsoft::WRL::ComPtr;
        using DirectX::SimpleMath::Vector3;

        class RENDERER_API DXDevice : public Graphics::RenderDevice
        {
            using Super = Graphics::RenderDevice;
        public:
            explicit DXDevice(HWND _WindowHandle);
            ~DXDevice();

        public:
            Graphics::RenderContext* Initalize() override;

            void MakeBuffers(const std::string& _Key, std::vector<Vertex>& _Vertices
                , std::vector<uint32_t>& _Indices) override;
        private:
            ComPtr<ID3D11Device> Device;

            UINT NumOfMultiSamplingLevel;
        };
    }
}


