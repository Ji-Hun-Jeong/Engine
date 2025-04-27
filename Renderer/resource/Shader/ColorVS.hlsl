#include "Common.hlsli"

cbuffer MeshConst : register(b0)
{
    matrix MVP;
}

PSInput main(VSInput input)
{
    PSInput output;
    output.position = float4(input.position, 1.0f);
    output.position = mul(output.position, MVP);
    output.color = input.color;
    return output;
};