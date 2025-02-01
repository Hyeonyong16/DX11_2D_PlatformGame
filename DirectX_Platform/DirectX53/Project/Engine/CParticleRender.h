#pragma once
#include "CRenderComponent.h"
#include "CParticleTickCS.h"

class CStructuredBuffer;

class CParticleRender :
    public CRenderComponent
{
private:
    CStructuredBuffer*      m_ParticleBuffer;
    CStructuredBuffer*      m_SpawnBuffer;


    Ptr<CParticleTickCS>    m_TickCS;
    UINT                    m_MaxParticle;      // ��ƼŬ �ִ� ����

    tParticleModule         m_Module;           // ��ƼŬ ���� ������
    float                   m_AccTime;          // �����ð� üũ


public:
    // �ʴ� ��ƼŬ ������ ����
    void SetSpawnRate(float _Rate) { m_Module.SpawnRate = _Rate; }
    float GetSpawnRate() { return m_Module.SpawnRate; }

public:
    virtual void FinalTick() override;
    virtual void Render() override;

private:
    void CreateMtrl();
    void CalcSpawnCount();


public:
    CLONE(CParticleRender);
    CParticleRender();
    ~CParticleRender();
};

