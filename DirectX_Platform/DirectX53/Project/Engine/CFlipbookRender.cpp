#include "pch.h"
#include "CFlipbookRender.h"

#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CTransform.h"
#include "CFlipbook.h"

CFlipbookRender::CFlipbookRender()
	: CRenderComponent(COMPONENT_TYPE::FLIPBOOKRENDER)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));

	CreateFlipbookMaterial();
}

CFlipbookRender::~CFlipbookRender()
{
}

void CFlipbookRender::FinalTick()
{
	if (nullptr == m_CurFlipbook)
		return;

	if (m_Finish)
	{
		if (m_Repeat)
		{
			m_SpriteIdx = 0;
			m_Finish = false;
		}
		else
		{
			return;
		}		
	}

	m_Time += DT;

	if ((1.f / m_FPS) < m_Time)
	{
		m_Time -= (1.f / m_FPS);

		++m_SpriteIdx;

		if (m_CurFlipbook->GetSpriteCount() <= m_SpriteIdx)
		{
			m_Finish = true;
			m_SpriteIdx -= 1;
		}
	}
}

void CFlipbookRender::Render()
{
	if (nullptr == m_CurFlipbook)
		return;

	// 현재 진행중인 프레임 스프라이트를 출력
	Ptr<CSprite> pCurSprite = m_CurFlipbook->GetSprite(m_SpriteIdx);
	Ptr<CTexture> pAtlas = pCurSprite->GetAtlasTex(); 
	Vec2 vLeftTop = pCurSprite->GetLeftTop();
	Vec2 vSlice = pCurSprite->GetSlice();
	Vec2 vBackground = pCurSprite->GetBackground();
	Vec2 vOffset = pCurSprite->GetOffset();

	// 위치정보 업데이트
	Transform()->Binding();

	// 사용할 쉐이더 바인딩	
	if (nullptr != pCurSprite)
	{
		GetMaterial()->SetScalarParam(INT_0, (int)!!pCurSprite->GetAtlasTex().Get());
		GetMaterial()->SetTexParam(TEX_0, pAtlas);
		GetMaterial()->SetScalarParam(VEC2_0, vLeftTop);
		GetMaterial()->SetScalarParam(VEC2_1, vSlice);
		GetMaterial()->SetScalarParam(VEC2_2, vBackground);
		GetMaterial()->SetScalarParam(VEC2_3, vOffset);
	}
	else
	{
		GetMaterial()->SetScalarParam(INT_0, 0);
		GetMaterial()->SetTexParam(TEX_0, nullptr);
	}

	GetMaterial()->Binding();

	// 렌더링 시작
	GetMesh()->Render();
}

void CFlipbookRender::CreateFlipbookMaterial()
{
	if (nullptr == CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"FlipbookShader"))
	{
		// FlipbookShader
		Ptr<CGraphicShader> pShader = new CGraphicShader;
		pShader->CreateVertexShader(L"HLSL\\flipbook.fx", "VS_Flipbook");
		pShader->CreatePixelShader(L"HLSL\\flipbook.fx", "PS_Flipbook");
		pShader->SetRSType(RS_TYPE::CULL_NONE);
		pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);
		CAssetMgr::GetInst()->AddAsset(L"FlipbookShader", pShader.Get());
	}

	if (nullptr == CAssetMgr::GetInst()->FindAsset<CMaterial>(L"FlipbookMtrl"))
	{
		// FlipbookMtrl
		Ptr<CMaterial> pMtrl = new CMaterial;
		pMtrl->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"FlipbookShader"));
		CAssetMgr::GetInst()->AddAsset(L"FlipbookMtrl", pMtrl.Get());
	}

	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"FlipbookMtrl"));
}

void CFlipbookRender::AddFlipbook(int _Idx, Ptr<CFlipbook> _Flipbook)
{
	if (m_vecFlipbook.size() <= _Idx)
	{
		m_vecFlipbook.resize(_Idx + 1);
	}

	m_vecFlipbook[_Idx] = _Flipbook;
}