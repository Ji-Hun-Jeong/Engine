#include "Common.hlsli"

struct VSInput
{
    float3 position : POSITION;
    float3 color : COLOR;
};
struct PSInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
};

cbuffer MeshConst : register(b2)
{
    matrix World;
}

PSInput main(VSInput input)
{
    PSInput output;
    output.position = float4(input.position, 1.0f);
    output.position = mul(output.position, World);
    output.position = mul(output.position, ViewProj);
    output.color = input.color;
    return output;
};