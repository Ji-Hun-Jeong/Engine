#pragma once
#include "Model/Model.h"
#include "DXResources.h"

namespace Graphics
{
    namespace DX
    {
        using Microsoft::WRL::ComPtr;
        class DXConstant : public Constant
        {
        public:
            ~DXConstant()
            {
                for (auto VCB : VertexConstBuffers)
                    VCB->Release();
            }
        private:
            std::vector<ID3D11Buffer*> VertexConstBuffers;
        };

        class DXModel : public Model
        {
        public:
            DXModel(DXResource& _Resource)
                : VertexBuffer(nullptr)
                , IndexBuffer(nullptr)
                , Stride(0)
                , IndexCount(0)
                , Resource(_Resource)
            {
                
            }
            ~DXModel()
            {
                if (VertexBuffer)
                    VertexBuffer->Release();
                if (IndexBuffer)
                    IndexBuffer->Release();
                
                for (auto PCB : PixelConstBuffers)
                    PCB->Release();
            }

        public:
            

        private:
            // 세팅할 때 get쓰지도 않게 그냥 포인터로
            ID3D11Buffer* VertexBuffer;
            ID3D11Buffer* IndexBuffer;
            
            std::vector<DXConstant*> VertexConstBuffers;
            std::vector<ID3D11Buffer*> PixelConstBuffers;

            UINT Stride;
            UINT IndexCount;

            DXResource& Resource;
        };
    }
    
}


