
struct VS_INPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

cbuffer CameraData : register(b0)
{
    Matrix View;
    Matrix Projection;
}
cbuffer TransformData : register(b1)
{
    Matrix WorldTransform;
}

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
    output.position = mul(input.position, WorldTransform);
    output.position = mul(input.position, View);
    output.position = mul(input.position, Projection);
	output.uv = input.uv;

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