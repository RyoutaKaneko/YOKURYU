#include "OBJ.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	float4 wnormal = normalize(mul(matWorld, float4(normal, 0)));
	float4 wpos = mul(matWorld, pos);

	VSOutput output; // ピクセルシェーダーに渡す値
	output.svpos = mul(mul(mul(projection,view), matWorld),pos);
	output.worldPos = wpos;
	output.normal = wnormal.xyz;
	output.uv = uv;
	return output;
}