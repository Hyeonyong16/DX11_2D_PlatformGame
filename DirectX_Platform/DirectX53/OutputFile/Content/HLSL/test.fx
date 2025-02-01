#ifndef _TEST
#define _TEST

#include "value.fx"

// RW : Read / Write
RWTexture2D<float4> g_TargetTex : register(u0);



// SV_GroupID           : �����尡 ���� �׷��� �ε���
// SV_GroupThreadID     : �����尡 ���� �׷� ������ �ش� �������� �ε���
// SV_GroupIndex        : �����尡 ���� �׷� ������ �ش� �������� �ε����� 1�������� ����
// SV_DispatchThreadID  : ��� �����带 ��Ʋ� �ش� �������� �ε���

// HLSL 5.0 ���� �׷�� ������ ���� : 1024
[numthreads(32, 32, 1)] // 1 Group �� ������ �� 240
void CS_Test(int3 _ID : SV_DispatchThreadID)
{
    g_TargetTex[_ID.xy] = float4(0.f, 0.f, 1.f, 1.f);
}

#endif