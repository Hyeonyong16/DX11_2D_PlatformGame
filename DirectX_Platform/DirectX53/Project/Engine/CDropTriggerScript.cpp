#include "pch.h"
#include "CDropTriggerScript.h"

#include "CTransform.h"

CDropTriggerScript::CDropTriggerScript()
{
}

CDropTriggerScript::~CDropTriggerScript()
{
}

void CDropTriggerScript::Tick()
{
}

void CDropTriggerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider)
{
	if (L"Parent" == _Other->GetName())
	{
		CTransform* pTransform = _Other->Transform();
		pTransform->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	}

}
