#pragma once
#include "CScript.h"
class CCameraMoveScript :
    public CScript
{
private:
    float   m_CamSpeed;
    CGameObject* m_Target;

public:
    virtual void Tick() override;

    void SetTarget(CGameObject* _Target) { m_Target = _Target; }

private:
    void Move_Perspective();
    void Move_OrthoGraphic();



public:
    CLONE(CCameraMoveScript);
public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

