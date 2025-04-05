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