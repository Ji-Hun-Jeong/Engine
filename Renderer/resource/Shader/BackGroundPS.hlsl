#include "Common.hlsli"

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

float4 main(PSInput _Input) : SV_TARGET
{
    float4 Color = Image.Sample(LinearSampler, _Input.uv);
    float4 FloorPixel = FloorSRV.Sample(PointSampler, _Input.uv);
    float4 MonsterWallPixel = MonsterWallSRV.Sample(PointSampler, _Input.uv);
    float4 LadderPixel = LadderSRV.Sample(PointSampler, _Input.uv);
    
    if (FloorPixel.r == 0.0f || FloorPixel.g == 0.0f || FloorPixel.b == 0.0f)
        Color = FloorPixel;
    if (MonsterWallPixel.r == 0.0f || MonsterWallPixel.g == 0.0f || MonsterWallPixel.b == 0.0f)
        Color = MonsterWallPixel;
    if (LadderPixel.r == 0.0f || LadderPixel.g == 0.0f || LadderPixel.b == 0.0f)
        Color = LadderPixel;
    
    return Color;

}