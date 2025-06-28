#include "Common.hlsli"


struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 Color = float4(0.0f, 1.0f, 1.0f, 1.0f);
    Color = Image.Sample(LinearSampler, input.uv);
    return Color;
}