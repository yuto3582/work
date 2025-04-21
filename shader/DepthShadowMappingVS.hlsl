#include "common.hlsl"

//�G���g���[�֐�
void main(in VS_IN In, out PS_IN Out)
{
	//���_�ϊ�����
    matrix wvp; //���[���h�r���[�v���W�F�N�V�����s��
    wvp = mul(World, View); //wvp = World�s�� * View�s��
    wvp = mul(wvp, Projection); //wvp = wvp + Projection�s��
    Out.Position = mul(In.Position, wvp); //���_���W��ϊ����ďo��
    
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    
    float light = -dot(Light.Direction.xyz, worldNormal.xyz);
    light = saturate(light);
    Out.Diffuse = light;
    Out.Diffuse.a = In.Diffuse.a;
    
    Out.Position = mul(In.Position, wvp);
    Out.Normal = worldNormal;
    Out.TexCoord = In.TexCoord;
    
    //���C�g�Tr��t���_�ϊ����ďo��
    matrix lightwvp;
    lightwvp = mul(World, Light.ViewMatrix);
    lightwvp = mul(lightwvp, Light.ProjectonMatrix);
    Out.LightPosition = mul(In.Position, lightwvp);
    
}

