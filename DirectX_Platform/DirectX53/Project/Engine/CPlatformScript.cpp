#include "pch.h"
#include "CPlatformScript.h"

#include "CRigidbody.h"

CPlatformScript::CPlatformScript()
{
}

CPlatformScript::~CPlatformScript()
{
}

void CPlatformScript::Tick()
{
}

void CPlatformScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider)
{
	if (L"Parent" == _Other->GetName())
	{
		CRigidbody* pBody = _Other->Rigidbody();
		pBody->SetGround(true);
	}
}

void CPlatformScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider)
{
	if (L"Parent" == _Other->GetName())
	{
		CRigidbody* pBody = _Other->Rigidbody();
		pBody->SetGround(false);
	}
}
