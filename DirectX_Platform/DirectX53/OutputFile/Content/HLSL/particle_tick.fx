#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"





RWStructuredBuffer<tParticle> g_Buffer : register(u0);
RWStructuredBuffer<tSpawnCount> g_Spawn : register(u1);



#define MAX_PARTICLE g_int_0

[numthreads(256, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    if (MAX_PARTICLE <= _ID.x)
        return;
    
    // �����尡 ����� ��ƼŬ�� ��Ȱ��ȭ ���¶��
    if (!g_Buffer[_ID.x].Active)
    {
        while (g_Spawn[0].SpawnCount)
        {
            int SpawnCount = g_Spawn[0].SpawnCount;            
            int Input = SpawnCount - 1;
            int Origin = 0;
        
            // Atomic �Լ�, �����尡 �ϳ��� ���������� ����
            InterlockedCompareExchange(g_Spawn[0].SpawnCount, SpawnCount, Input, Origin);
            //InterlockedExchange(g_Spawn[0].SpawnCount, Input, Origin);
        
            // ���� ������ �����常 Origin ���� 1�� �����´�.
            if (Origin == SpawnCount)
            {
                g_Buffer[_ID.x].Active = true;
                break;
            }
        }
    }    
    //g_Buffer[_ID.x].WorldPos += g_Buffer[_ID.x].Velocity * g_DT;
}

#endif