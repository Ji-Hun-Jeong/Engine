#include "Common.hlsli"

RWStructuredBuffer<float3> Positions : register(u0);
RWStructuredBuffer<int> CollisionWhethers : register(u1);
RWStructuredBuffer<int> CollisionStates : register(u2);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    if(CollisionWhethers[DTid.x] == 0)
        return;
    if(Positions[DTid.x].x > 0.3f)
    {
        Positions[DTid.x].x = 0.3f;
    }
}