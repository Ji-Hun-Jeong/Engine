#pragma once
#include "Renderer/src/Render/RenderDevice.h"
#include "DX.h"
#include "DXResources.h"

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
            RenderContext* Initalize() override;

            void MakeGeometryBuffers(const std::string& _Key, std::vector<Vertex>& _Vertices
                , std::vector<uint32_t>& _Indices) override;
            void MakeVSConstBuffer(const std::string& _Key, eCategoryVSConst _VSConstType
                , UINT _ConstDataSize) override
            {
                auto Iter = DXResource::DXBuffers.find(_Key);
                if (Iter == DXResource::DXBuffers.end())
                    assert(0);
                
                DXBuffers* Buffers = Iter->second;
                
                D3D11_BUFFER_DESC BufferDesc;
                ZeroMemory(&BufferDesc, sizeof(BufferDesc));
                BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
                BufferDesc.ByteWidth = _ConstDataSize;
                BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                BufferDesc.StructureByteStride = 0;

                HRESULT hr = Device->CreateBuffer(&BufferDesc, nullptr, Buffers->VSConstBuffer[(UINT)_VSConstType].GetAddressOf());
                if (FAILED(hr)) assert(0);

            }
            void MakePSConstBuffer(const std::string& _Key, eCategoryPSConst _PSConstType
                , UINT _ConstDataSize) override
            {
                auto Iter = DXResource::DXBuffers.find(_Key);
                if (Iter == DXResource::DXBuffers.end())
                    assert(0);

                DXBuffers* Buffers = Iter->second;

                D3D11_BUFFER_DESC BufferDesc;
                ZeroMemory(&BufferDesc, sizeof(BufferDesc));
                BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
                BufferDesc.ByteWidth = _ConstDataSize;
                BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                BufferDesc.StructureByteStride = 0;

                HRESULT hr = Device->CreateBuffer(&BufferDesc, nullptr, Buffers->PSConstBuffer[(UINT)_PSConstType].GetAddressOf());
                if (FAILED(hr)) assert(0);
            }

        private:
            ComPtr<ID3D11Device> Device;

            UINT NumOfMultiSamplingLevel;

            
        };
    }
}


