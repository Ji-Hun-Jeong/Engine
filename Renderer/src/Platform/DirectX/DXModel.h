#pragma once
#include "DX.h"

namespace Graphics
{
    namespace DX
    {
        using Microsoft::WRL::ComPtr;
        class DXConstant
        {
        public:
            DXConstant() {}
            ~DXConstant()
            {
                for (auto VCB : VertexConstBuffers)
                    VCB->Release();
            }

        private:
            std::vector<ID3D11Buffer*> VertexConstBuffers;

        };

        class DXModel
        {
        public:
            DXModel()
                : VertexBuffer(nullptr)
                , IndexBuffer(nullptr)
                , Stride(0)
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

        private:
            // ������ �� get������ �ʰ� �׳� �����ͷ�
            ID3D11Buffer* VertexBuffer;
            ID3D11Buffer* IndexBuffer;
            
            std::vector<DXConstant*> VertexConstBuffers;
            std::vector<ID3D11Buffer*> PixelConstBuffers;

            UINT Stride;
            UINT IndexCount;
        };

    }
    
}


