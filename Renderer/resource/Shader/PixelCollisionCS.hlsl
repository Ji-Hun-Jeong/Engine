#include "Common.hlsli"

RWStructuredBuffer<float3> Positions : register(u0);
RWStructuredBuffer<int> CollisionWhethers : register(u1);
RWStructuredBuffer<int> CollisionStates : register(u2);


bool Collision(float3 _Position, uint _ImageWidth, uint _ImageHeight, uint2 _OffsetPixel, Texture2D _Image)
{
    float U = clamp((_Position.x + 1) * _ImageWidth / 2, 0, _ImageWidth - 1);
    float V = clamp((-_Position.y + 1) * _ImageHeight / 2, 0, _ImageHeight - 1);
    for (uint i = -_OffsetPixel.x; i <= _OffsetPixel.x; ++i)
    {
        for (uint j = -_OffsetPixel.y; j <= _OffsetPixel.y; ++j)
        {
            float2 UV = float2((U + i) / _ImageWidth, (V + j) / _ImageHeight);
            float4 PixelColor = _Image.SampleLevel(PointSampler, UV, 0);
            if (PixelColor.r == 1.0f || PixelColor.g == 0.0f || PixelColor.b == 0.0f)
                return true;
        }
    }
    return false;
}
[numthreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (CollisionWhethers[DTid.x] == 0)
        return;

    float3 Position = Positions[DTid.x];

    uint ImageWidth = 0;
    uint ImageHeight = 0;
    FloorSRV.GetDimensions(ImageWidth, ImageHeight);
    
    float X = clamp((Position.x + 1) * ScreenWidth / 2, 0, ScreenWidth);
    float Y = clamp((-Position.y + 1) * ScreenHeight / 2, 0, ScreenHeight);
    float2 UV = float2(X / ImageWidth, Y / ImageHeight);
    float4 PixelColor = Image.SampleLevel(PointSampler, UV, 0);
    Positions[1] = float3(ScreenWidth, Y, 0.0f);
    // if (Collision(Position, ImageWidth, ImageHeight, uint2(100, 0), LadderSRV))
    //     Positions[1] = float3(0.26f, 0.46f, 0.76f);

}