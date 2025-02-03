#include "pch.h"
#include "CBackgroundScript.h"

#include "CCamera.h"
#include "CTransform.h"

CBackgroundScript::CBackgroundScript()
	: m_Target(nullptr)
{
}

CBackgroundScript::~CBackgroundScript()
{
}

void CBackgroundScript::Tick()
{
	if (nullptr == m_Target)
		return;

	CTransform* pOwnerTrans = CComponent::GetOwner()->Transform();
	CTransform* pTargetTrans = m_Target->Transform();
	pOwnerTrans->SetRelativePos(Vec3(pTargetTrans->GetRelativePos().x, pTargetTrans->GetRelativePos().y, pOwnerTrans->GetRelativePos().z));
}

