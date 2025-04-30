#pragma once
#include "Renderer/src/Render/RenderDevice.h"
#include "Renderer/include/WICTextureLoader.h"
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

            void MakeGeometryBuffers(const Str::FString& _Key, void* _Data, size_t _VertexSize, size_t _NumOfVertex
                , std::vector<uint32_t>& _Indices) override;
            void MakeVSConstBuffer(const Str::FString& _Key, eCategoryVSConst _VSConstType
                , UINT _ConstDataSize) override
            {
                auto Iter = Resource.DXBuffers.find(_Key);
                if (Iter == Resource.DXBuffers.end())
                    assert(0);
                
                DXBuffers* Buffers = Iter->second;
                
                D3D11_BUFFER_DESC BufferDesc;
                ZeroMemory(&BufferDesc, sizeof(BufferDesc));
                BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
                BufferDesc.ByteWidth = _ConstDataSize;
                BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                BufferDesc.StructureByteStride = 0;

                HRESULT hr = Resource.Device->CreateBuffer(&BufferDesc, nullptr, Buffers->VSConstBuffer[(UINT)_VSConstType].GetAddressOf());
                if (FAILED(hr)) assert(0);

            }
            void MakePSConstBuffer(const Str::FString& _Key, eCategoryPSConst _PSConstType
                , UINT _ConstDataSize) override
            {
                auto Iter = Resource.DXBuffers.find(_Key);
                if (Iter == Resource.DXBuffers.end())
                    assert(0);

                DXBuffers* Buffers = Iter->second;

                D3D11_BUFFER_DESC BufferDesc;
                ZeroMemory(&BufferDesc, sizeof(BufferDesc));
                BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
                BufferDesc.ByteWidth = _ConstDataSize;
                BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                BufferDesc.StructureByteStride = 0;

                HRESULT hr = Resource.Device->CreateBuffer(&BufferDesc, nullptr, Buffers->PSConstBuffer[(UINT)_PSConstType].GetAddressOf());
                if (FAILED(hr)) assert(0);
            }

            void LoadSRV(const Str::FString& _Path, const Str::FString& _ImageName) override
            {
                if (Resource.Images.find(_ImageName) != Resource.Images.end())
                    return;

                std::wstring WPath = _Path.GetWString();
                ID3D11ShaderResourceView* Image = nullptr;
                HRESULT HR = DirectX::CreateWICTextureFromFile(Resource.Device.Get(), WPath.c_str(), nullptr, &Image);
                if (FAILED(HR))
                    assert(0);

                Resource.Images.insert(std::make_pair(_ImageName, Image));
                Image->Release();
            }

        private:
            DXResource Resource;

            

            
        };
    }
}


