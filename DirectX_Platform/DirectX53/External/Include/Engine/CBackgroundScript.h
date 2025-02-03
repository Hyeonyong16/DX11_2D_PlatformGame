#pragma once
#include "CScript.h"
class CBackgroundScript :
    public CScript
{
private:
    CGameObject* m_Target;

public:
    virtual void Tick() override;

    void SetTarget(CGameObject* _Target) { m_Target = _Target; }

public:
    CLONE(CBackgroundScript);
    CBackgroundScript();
    ~CBackgroundScript();
};

