#include "FBX.hlsli"
//�G���g���[�|�C���g
//VSOutput main(VSInput input) {
//	//�@���Ƀ��[���h�s��ɂ���]�E�X�P�[�����O��K�p
//	float4 wnormal = normalize(mul(world, float4(input.normal, 0)));
//	//�s�N�Z���V�F�[�_�[�ɓn���l
//	VSOutput output;
//	//�s��ɂ����W�ϊ�
//	output.svpos = mul(mul(viewproj, world), input.pos);
//	//���[���h�@�������̃X�e�[�W�Ɉڂ�
//	output.normal = wnormal.xyz;
//	//���͒l�����̂܂܎��̃X�e�[�W�ɓn��
//	output.uv = input.uv;
//
//	return output;
//}
//�G���g���[�|�C���g
VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos = mul(mul(mul(projection, view), matWorld), pos);
	output.normal = normal;
	output.uv = uv;
	return output;
}