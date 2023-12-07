
struct VS_INPUT
{
    float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4  position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer TransformData : register(b0)
{
    Matrix WorldTransform;
    Matrix View;
    Matrix Projection;
}

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(float4(input.position, 1.f), WorldTransform);
    output.color = input.color;

    return output;
}

Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.color;
}