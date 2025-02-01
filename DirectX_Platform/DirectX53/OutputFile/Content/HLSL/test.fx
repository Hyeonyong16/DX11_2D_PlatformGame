#ifndef _TEST
#define _TEST

#include "value.fx"

// RW : Read / Write
RWTexture2D<float4> g_TargetTex : register(u0);



// SV_GroupID           : 스레드가 속한 그룹의 인덱스
// SV_GroupThreadID     : 스레드가 속한 그룹 내에서 해당 스레드의 인덱스
// SV_GroupIndex        : 스레드가 속한 그룹 내에서 해당 스레드의 인덱스를 1차원으로 변경
// SV_DispatchThreadID  : 모든 스레드를 통틀어서 해당 스레드의 인덱스

// HLSL 5.0 기준 그룹당 스레드 제한 : 1024
[numthreads(32, 32, 1)] // 1 Group 당 스레드 수 240
void CS_Test(int3 _ID : SV_DispatchThreadID)
{
    g_TargetTex[_ID.xy] = float4(0.f, 0.f, 1.f, 1.f);
}

#endif