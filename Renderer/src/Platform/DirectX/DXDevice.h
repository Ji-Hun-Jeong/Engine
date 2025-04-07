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

            void MakeGeometryBuffers(const std::string& _Key, std::vector<Vertex>& _Vertices
                , std::vector<uint32_t>& _Indices) override;
            void MakeConstBuffer()
            {
				D3D11_BUFFER_DESC BufferDesc;
				ZeroMemory(&BufferDesc, sizeof(BufferDesc));
				BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
				BufferDesc.ByteWidth = UINT(sizeof(Vertex) * _Vertices.size());
				BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				BufferDesc.CPUAccessFlags = 0;
				BufferDesc.StructureByteStride = sizeof(Vertex);

				D3D11_SUBRESOURCE_DATA BufferData = { 0 };
				BufferData.pSysMem = _Vertices.data();
				BufferData.SysMemPitch = 0;
				BufferData.SysMemSlicePitch = 0;
				HRESULT hr = Device->CreateBuffer(&BufferDesc, &BufferData, Buffers->VertexBuffer.GetAddressOf());
				if (FAILED(hr)) assert(0);

				_Vertices.clear();
            }

        private:
            ComPtr<ID3D11Device> Device;

            UINT NumOfMultiSamplingLevel;
        };
    }
}


