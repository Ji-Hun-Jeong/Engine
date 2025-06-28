#include "Common.hlsli"

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

float4 main(PSInput _Input) : SV_TARGET
{
    // BlendState적용중이라 뒷배경 보고싶으면 a값을 0으로
    float4 Color = float4(0.0f, 0.0f, 0.0f, 1.0f);
    Color = Image.Sample(LinearSampler, _Input.uv);
    float4 FloorPixel = FloorSRV.Sample(PointSampler, _Input.uv);
    float4 MonsterWallPixel = MonsterWallSRV.Sample(PointSampler, _Input.uv);
    float4 LadderPixel = LadderSRV.Sample(PointSampler, _Input.uv);
    float4 WallPixel = WallSRV.Sample(PointSampler, _Input.uv);
    
    if (FloorPixel.r != 1.0f || FloorPixel.g != 1.0f || FloorPixel.b != 1.0f)
        Color = FloorPixel;
    if (MonsterWallPixel.r != 1.0f || MonsterWallPixel.g != 1.0f || MonsterWallPixel.b != 1.0f)
        Color = MonsterWallPixel;
    if (LadderPixel.r != 1.0f || LadderPixel.g != 1.0f || LadderPixel.b != 1.0f)
        Color = LadderPixel;
    if (WallPixel.r != 1.0f || WallPixel.g != 1.0f || WallPixel.b != 1.0f)
        Color = WallPixel;
    
    return Color;

}