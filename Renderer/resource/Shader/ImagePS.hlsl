#include "Common.hlsli"
Texture2D Image : register(t0);

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 FloorPixel = FloorSRV.Sample(PointSampler, input.uv);
    if (FloorPixel.r == 1.0f && FloorPixel.g == 0.0f && FloorPixel.b == 1.0f)
        return float4(1.0f, 0.0f, 1.0f, 1.0f);
    
    return Image.Sample(LinearSampler, input.uv);
}