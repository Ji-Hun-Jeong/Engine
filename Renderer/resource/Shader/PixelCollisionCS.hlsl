#include "Common.hlsli"

RWStructuredBuffer<float3> Positions : register(u0);
RWStructuredBuffer<int> CollisionWhethers : register(u1);
RWStructuredBuffer<int> CollisionStates : register(u2);

float2 ConvertWorldPositionToImageUV(float3 _Position, uint2 _ImageScale)
{
    _Position.xy *= float2(ScreenWidth, ScreenHeight) / float2(_ImageScale);
    
    float2 UV = clamp((_Position.xy * float2(1.0f, -1.0f) + 1.0f) / 2.0f, 0.0f, 1.0f);
    
    return UV;
}
void ConvertImageUVToWorldPosition(inout float3 _Position, float2 _UV, uint2 _ImageScale)
{
    _Position = float3((_UV * 2.0f - 1.0f) * float2(1.0f, -1.0f), _Position.z);
    _Position.xy *= float2(_ImageScale) / float2(ScreenWidth, ScreenHeight);
}

bool Collision(inout float3 _Position, float2 _UV, uint2 _ImageScale, int2 _OffsetPixel, Texture2D _Image)
{
    uint2 OriginPosition = _UV * _ImageScale;
    
    for (int i = -_OffsetPixel.x; i < _OffsetPixel.x; ++i)
    {
        float2 Position = OriginPosition + int2(i, 0);
        float2 UV = Position / float2(_ImageScale);
        float4 PixelColor = _Image.SampleLevel(PointSampler, UV, 0);
        
        if (PixelColor.r != 1.0f || PixelColor.g != 1.0f || PixelColor.b != 1.0f)
        {
            ConvertImageUVToWorldPosition(_Position, UV, _ImageScale);
            return true;
        }
           
    }
    
    for (int j = -_OffsetPixel.y; j < _OffsetPixel.y; ++j)
    {
        float2 Position = OriginPosition + int2(0, j);
        float2 UV = Position / float2(_ImageScale);
        float4 PixelColor = _Image.SampleLevel(PointSampler, UV, 0);
        
        if (PixelColor.r != 1.0f || PixelColor.g != 1.0f || PixelColor.b != 1.0f)
        {
            ConvertImageUVToWorldPosition(_Position, UV, _ImageScale);
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
    
    uint Index = DTid.x;

    float3 Position = Positions[DTid.x];

    uint ImageWidth = 0;
    uint ImageHeight = 0;
    FloorSRV.GetDimensions(ImageWidth, ImageHeight);
    
    float2 UV = ConvertWorldPositionToImageUV(Position, uint2(ImageWidth, ImageHeight));
    
    CollisionStates[Index] = 0;
    if (Collision(Position, UV, uint2(ImageWidth, ImageHeight), int2(0, 2), FloorSRV))
    {
        Positions[Index] = Position;
        CollisionStates[Index] |= 1;
    }
    if (Collision(Position, UV, uint2(ImageWidth, ImageHeight), int2(20, 0), WallSRV))
    {
        CollisionStates[Index] |= 1 << 1;
    }
    if (Collision(Position, UV, uint2(ImageWidth, ImageHeight), int2(20, 0), LadderSRV))
    {
        CollisionStates[Index] |= 1 << 2;
    }
    if (Collision(Position, UV, uint2(ImageWidth, ImageHeight), int2(20, 0), RopeSRV))
    {
        CollisionStates[Index] |= 1 << 3;
    }
    if (Collision(Position, UV, uint2(ImageWidth, ImageHeight), int2(20, 0), MonsterWallSRV))
    {
        CollisionStates[Index] |= 1 << 4;
    }
    
}