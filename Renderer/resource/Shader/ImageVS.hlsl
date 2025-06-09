#include "Common.hlsli"

struct VSInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

cbuffer MeshConst : register(b2)
{
    matrix World;
    int Direction;
    float3 Dummy1;
}

PSInput main(VSInput input)
{
    PSInput output;
    output.position = float4(input.position, 1.0f);
    output.position = mul(output.position, World);
    output.uv = input.uv;
    if(Direction > 0)
        output.uv.x = -output.uv.x;
    return output;
};