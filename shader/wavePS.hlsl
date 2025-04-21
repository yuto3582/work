#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

static float PI = 3.141592653589;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�����x�N�g��
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    //�@���x�N�g��
    float3 normal = normalize(In.Normal.xyz);
    
    //����
    float3 refColor;
    {
        //���˃x�N�g��
        float3 refv = reflect(eyev, normal); //���˂̃x�N�g����reflect()
        refv = normalize(refv);
    
        //���}�b�s���O�e�N�X�`�����W(�X�t�B�A�}�b�v)

        //float2 envTexCoord;
        //envTexCoord.x = refv.x * 0.3f + 0.5f;
        //envTexCoord.y = -refv.y * 0.3f + 0.5f;
	
        //���}�b�s���O�e�N�X�`�����W(�p�m���})
        float2 envTexCoord;
        envTexCoord.x = atan(refv.x * refv.z) / (PI * 2);
        envTexCoord.y = acos(refv.y) / PI;
	
        refColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
        
    }
    
    //����
    float3 refrColor;
    {
        //���܃x�N�g��
        float3 refrv = refract(eyev.xyz, normal, 1.0f / 1.5f); //���܃x�N�g����refract()
        refrv = normalize(refrv);
    
    
        //���}�b�s���O�e�N�X�`�����W(�p�m���})
        float2 envTexCoord;
        envTexCoord.x = atan(refrv.x * refrv.z) / (PI * 2);
        envTexCoord.y = acos(refrv.y) / PI;

        //���܃}�b�s���O
        refrColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    }
    
    float f0 = 0.04f;
    float d = saturate(dot(-eyev, normal));
    float fresnel = f0 + (1.0f - f0) * pow((1.0f - d), 5.0f);

    //outDiffuse.rgb = lerp(refrColor, refColor, fresnel);
    outDiffuse.rgb = refColor;
    outDiffuse.a = fresnel;

}

