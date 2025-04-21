#include "common.hlsl"

Texture2D	g_Texture : register(t0);			//0�ԃe�N�X�`���̏��
SamplerState g_SamplerState : register(s0);		//�T���v���[0��


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�e�N�X�`���̐F���擾
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;		//�e�N�X�`���̐F�ɒ��_�̖��邳����Z

	//outDiffuse = In.Diffuse;		//�s�N�Z���̖��邳�Œ��ڕ`��



}

