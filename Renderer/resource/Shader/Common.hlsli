cbuffer CameraConst : register(b1)
{
    matrix ViewProj;
}

Texture2D FloorSRV : register(t1);
Texture2D WallSRV : register(t2);
Texture2D LadderSRV : register(t3);
Texture2D RopeSRV : register(t4);
Texture2D MonsterWallSRV : register(t5);

SamplerState LinearSampler : register(s0);
SamplerState PointSampler : register(s1);