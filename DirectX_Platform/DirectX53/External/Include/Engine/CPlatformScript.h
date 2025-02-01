#pragma once
#include "CScript.h"

class CPlatformScript :
    public CScript
{
private:

public:
    virtual void Tick() override;
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider) override;

public:
    CLONE(CPlatformScript);
    CPlatformScript();
    ~CPlatformScript();
};

