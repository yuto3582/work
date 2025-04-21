
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

	Out.Diffuse = In.Diffuse;				//���_�E�̏o��
	Out.TexCoord = In.TexCoord;				//�e�N�X�`�����W�̏o��

	Out.WorldPosition = mul(In.Position, World);

}