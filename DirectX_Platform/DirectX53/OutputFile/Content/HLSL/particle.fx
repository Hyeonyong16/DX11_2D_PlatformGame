#ifndef _PARTICLE
#define _PARTICLE

#include "value.fx"

StructuredBuffer<tParticle> m_Buffer : register(t20);

struct VS_IN
{    
    uint InstID : SV_InstanceID;
};


struct VS_OUT
{
    float InstID : FOG;
};

VS_OUT VS_Particle(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    output.InstID = _in.InstID;      
    return output;
}

struct GS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

// 1. ������ �����ϱ�
// 2. ��Ȱ��ȭ �� ��ƼŬ�� �ǳʶٱ�
[maxvertexcount(6)]
void GS_Particle(point VS_OUT _in[1], inout TriangleStream<GS_OUT> _Stream)
{
    uint InstID = (uint)_in[0].InstID;    
    if (false == m_Buffer[InstID].Active)
        return;
        
    GS_OUT output[4] = { (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f };
    
    float3 vViewPos = mul(float4(m_Buffer[InstID].WorldPos.xyz, 1.f), g_matView).xyz;    
    //float3 vViewPos = m_Buffer[InstID].WorldPos.xyz;
    
    float3 vScale = m_Buffer[InstID].WorldScale.xyz;
    
    output[0].vPosition.xyz = float3(vViewPos.x - vScale.x / 2.f, vViewPos.y + vScale.y / 2.f, vViewPos.z);
    output[1].vPosition.xyz = float3(vViewPos.x + vScale.x / 2.f, vViewPos.y + vScale.y / 2.f, vViewPos.z);
    output[2].vPosition.xyz = float3(vViewPos.x + vScale.x / 2.f, vViewPos.y - vScale.y / 2.f, vViewPos.z);
    output[3].vPosition.xyz = float3(vViewPos.x - vScale.x / 2.f, vViewPos.y - vScale.y / 2.f, vViewPos.z);
    
    for (int i = 0; i < 4; ++i)
    {
        output[i].vPosition = mul(float4(output[i].vPosition.xyz, 1.f), g_matProj);
    }
    
    output[0].vUV = float2(0.f, 0.f);
    output[1].vUV = float2(1.f, 0.f);
    output[2].vUV = float2(1.f, 1.f);
    output[3].vUV = float2(0.f, 1.f);
        
    _Stream.Append(output[0]);
    _Stream.Append(output[1]);
    _Stream.Append(output[2]);
    _Stream.RestartStrip();

    _Stream.Append(output[0]);
    _Stream.Append(output[2]);
    _Stream.Append(output[3]);
    _Stream.RestartStrip();
}

float4 PS_Particle(GS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);    
    vColor.rgb *= float3(2.f, 1.f, 1.f);
    return vColor;
}

#endif