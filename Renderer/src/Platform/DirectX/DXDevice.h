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
                , const ConstData& _ConstData) override
            {
                auto Iter = DXResource::DXBuffers.find(_Key);
                if (Iter == DXResource::DXBuffers.end())
                    assert(0);
                
                // 구조체 맨 앞에 vfptr때문에 이상함.
                DXBuffers* Buffers = Iter->second;
                
                D3D11_BUFFER_DESC BufferDesc;
                ZeroMemory(&BufferDesc, sizeof(BufferDesc));
                BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
                BufferDesc.ByteWidth = _ConstData.SizeOf();
                BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                BufferDesc.StructureByteStride = 0;


                HRESULT hr = Device->CreateBuffer(&BufferDesc, nullptr, Buffers->VSConstBuffer[(UINT)_VSConstType].GetAddressOf());
                if (FAILED(hr)) assert(0);

            }
            void MakePSConstBuffer(const std::string& _Key, eCategoryPSConst _PSConstType
                , const ConstData& _ConstData) override
            {
                auto Iter = DXResource::DXBuffers.find(_Key);
                if (Iter == DXResource::DXBuffers.end())
                    assert(0);

                DXBuffers* Buffers = Iter->second;

                D3D11_BUFFER_DESC BufferDesc;
                ZeroMemory(&BufferDesc, sizeof(BufferDesc));
                BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
                BufferDesc.ByteWidth = _ConstData.SizeOf();
                BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                BufferDesc.StructureByteStride = 0;

                D3D11_SUBRESOURCE_DATA BufferData = { 0 };
                BufferData.pSysMem = &_ConstData;
                BufferData.SysMemPitch = 0;
                BufferData.SysMemSlicePitch = 0;
                HRESULT hr = Device->CreateBuffer(&BufferDesc, &BufferData, Buffers->PSConstBuffer[(UINT)_PSConstType].GetAddressOf());
                if (FAILED(hr)) assert(0);
            }

        private:
            ComPtr<ID3D11Device> Device;

            UINT NumOfMultiSamplingLevel;

            
        };
    }
}


