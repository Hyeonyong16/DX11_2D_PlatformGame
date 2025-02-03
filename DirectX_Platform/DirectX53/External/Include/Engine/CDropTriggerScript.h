#pragma once
#include "CScript.h"
class CDropTriggerScript :
    public CScript
{
private:

public:
    virtual void Tick() override;
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider) override;

public:
    CLONE(CDropTriggerScript);
    CDropTriggerScript();
    ~CDropTriggerScript();

};

