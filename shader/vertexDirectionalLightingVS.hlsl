

#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	//���_�̕ϊ�
	matrix wvp;
	wvp = mul(World, View);					//wvp = World�s��*View�s��
	wvp = mul(wvp, Projection);				//wvp = wvp * Projection
	Out.Position = mul(In.Position, wvp);	//���_���W*wvp�̌��ʂ��o��

	//�@�������[���h�s��ŉ�]������(���_�Ɠ�����]��������)
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0f);		//w��0�Ƃ��ăR�s�[����
	worldNormal = mul(normal, World);			//�R�s�[�����@��*World�s��
	worldNormal = normalize(worldNormal);		//�@���𐳋K������
	Out.Normal = worldNormal;					//��]��̖@�����o��	In.Normal�ł͂Ȃ�

	//�����v�Z	���x�N�g���Ɩ@���x�N�g���̓���
	float	light = -dot(Light.Direction.xyz, worldNormal.xyz);
	//float	light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);		//�n�[�t�����o�[�g�ł̖��邳�̌v�Z
	light = saturate(light);		//light�̒l��0.0-1.0�ŖO�a������

	//���_�̃f�B�t���[�Y���o��
	Out.Diffuse.rgb = light;		//���邳�̒l�𒸓_�F�Ƃ��ďo��
	Out.Diffuse.a = In.Diffuse.a;	//���͒��_�̏������̂܂܏o��

	//�e�N�X�`�����W���o��
	Out.TexCoord = In.TexCoord;
}