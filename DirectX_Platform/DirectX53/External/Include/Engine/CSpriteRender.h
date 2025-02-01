#pragma once
#include "CRenderComponent.h"

#include "CSprite.h"

class CSpriteRender :
    public CRenderComponent
{
private:
    Ptr<CSprite>    m_Sprite;


public:
    void SetSprite(Ptr<CSprite> _Sprite) { m_Sprite = _Sprite; }   


private:
    void CreateSpriteMaterial();

public:
    virtual void FinalTick() override;
    virtual void Render() override;

public:
    CLONE(CSpriteRender);
    CSpriteRender();
    ~CSpriteRender();
};

