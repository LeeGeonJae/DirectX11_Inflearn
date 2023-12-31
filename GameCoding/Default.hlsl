
struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

cbuffer CameraData : register(b0)
{
    row_major Matrix View;
    row_major Matrix Projection;
}
cbuffer TransformData : register(b1)
{
    Matrix WorldTransform;
}
cbuffer AnimationData : register(b2)
{
    float2 spriteOffset;
    float2 spriteSize;
    float2 textureSize;
    float useAnimation;
}

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(float4(input.position, 1.f), WorldTransform);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    output.uv = input.uv;

    if (useAnimation == 1.f)
    {
        output.uv *= spriteSize / textureSize;
        output.uv += spriteOffset / textureSize;
    }
    
    return output;
}

Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = texture0.Sample(sampler0, input.uv);
	
    return color;
}