#pragma once
#include "Renderer/RenderDevice.h"
#include "DX.h"

namespace Graphics
{
    namespace DX
    {
        using Microsoft::WRL::ComPtr;
        using DirectX::SimpleMath::Vector3;

        class DXDevice : public RenderDevice
        {
            using Super = RenderDevice;
        public:
            explicit DXDevice(HWND _WindowHandle);

        public:
            class RenderContext* Initalize() override;

            void MakeBuffers(const std::string& _Key, std::vector<Vertex>& _Vertices
                , std::vector<uint32_t>& _Indices) override;

        private:
            ComPtr<ID3D11Device> Device;
        };
    }
}


