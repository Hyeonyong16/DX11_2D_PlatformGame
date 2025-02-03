#include "pch.h"
#include "CPlatformScript.h"

#include "CRigidbody.h"
#include "CTransform.h"
#include "CCollider2D.h"

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
		CTransform* pTrans = _Other->Transform();
		CTransform* pOwnerTrans = CComponent::GetOwner()->Transform();

		float ownerPosX = pTrans->GetRelativePos().x;
		float platformPosX = pOwnerTrans->GetRelativePos().x;
		float ownerScaleX = _OtherCollider->GetScale().x / 2;
		float platformScaleX = pOwnerTrans->GetRelativeScale().x / 2;

		if (ownerPosX < platformPosX - platformScaleX - ownerScaleX + 1.f
			|| ownerPosX > platformPosX + platformScaleX + ownerScaleX - 1.f)
			return;

		CRigidbody* pBody = _Other->Rigidbody();
		pBody->SetGround(true);
	}
}

void CPlatformScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _Other, CCollider2D* _OtherCollider)
{
	if (L"Parent" == _Other->GetName())
	{
		CRigidbody* pBody = _Other->Rigidbody();
		if(pBody->IsGround())
			pBody->SetGround(false);
	}
}
