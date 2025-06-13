cbuffer CameraConst : register(b1)
{
    matrix ViewProj;
    matrix InvViewProj;
    uint ScreenWidth;
    uint ScreenHeight;
    float2 CameraDummy;
}

Texture2D Image : register(t0);
Texture2D FloorSRV : register(t1);
Texture2D WallSRV : register(t2);
Texture2D LadderSRV : register(t3);
Texture2D RopeSRV : register(t4);
Texture2D MonsterWallSRV : register(t5);

SamplerState LinearSampler : register(s0);
SamplerState PointSampler : register(s1);