SamplerState LinearSampler : register(s0);
Texture2D Image : register(t0);

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    return Image.Sample(LinearSampler, input.uv);
}