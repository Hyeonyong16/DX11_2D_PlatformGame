#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "assets.h"

void CAssetMgr::Init()
{
	CreateEngineMesh();

	CreateEngineTexture();

	CreateEngineSprite();

	CreateEngineGraphicShader();

	CreateEngineComputeShader();

	CreateEngineMaterial();
}

void CAssetMgr::CreateEngineMesh()
{
	// =========
	// PointMesh
	// =========
	Ptr<CMesh> pMesh = new CMesh;
	Vtx vPoint;
	vPoint.vPos = Vec3(0.f, 0.f, 0.f);
	vPoint.vUV = Vec2(0.f, 0.f);
	vPoint.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	UINT Idx = 0;
	pMesh->Create(&vPoint, 1, &Idx, 1);
	AddAsset(L"PointMesh", pMesh.Get());

	// ========
	// RectMesh
	// ========	
	// 0 -- 1
	// | \  |
	// 3 -- 2
	pMesh = new CMesh;
	pMesh->SetName(L"RectMesh");

	Vtx arrVtx[4] = {};
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);

	// Index
	UINT arrIdx[6] = { 0, 1, 2, 0, 2, 3 };

	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh.Get());


	// ==============
	// RectMesh_Debug
	// ==============	
	// 0 -- 1
	// | \  |
	// 3 -- 2
	pMesh = new CMesh;
	pMesh->SetName(L"RectMesh_Debug");

	arrIdx[0] = 0; arrIdx[1] = 1; arrIdx[2] = 2; arrIdx[3] = 3; arrIdx[4] = 0; 
	pMesh->Create(arrVtx, 4, arrIdx, 5);
	AddAsset(L"RectMesh_Debug", pMesh.Get());

	// ==========
	// CircleMesh
	// ==========
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;


	pMesh = new CMesh;
	pMesh->SetName(L"CircleMesh");

	// Circle �߽���
	Vtx v;
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.5f, 0.5f);
	vecVtx.push_back(v);

	int Slice = 40;
	float Radius = 0.5f;
	float Angle = 0.f;

	// Circle �׵θ� ����
	for (int i = 0; i < Slice + 1; ++i)
	{
		v.vPos = Vec3(Radius * cosf(Angle), Radius * sinf(Angle), 0.f);		
		v.vUV = Vec2(v.vPos.x + 0.5f, 1.f - (v.vPos.y + 0.5f));
		vecVtx.push_back(v);

		Angle += XM_2PI / (float)Slice;
	}

	// Circle �ε���
	for(int i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh", pMesh.Get());	
	vecIdx.clear();

	// ================
	// CircleMesh_Debug
	// ================
	pMesh = new CMesh;
	pMesh->SetName(L"CircleMesh_Debug");

	for (size_t i = 0; i < vecVtx.size() - 1; ++i)
	{
		vecIdx.push_back(i + 1);
	}
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh_Debug", pMesh.Get());
	vecVtx.clear();
	vecIdx.clear();
}

void CAssetMgr::CreateEngineTexture()
{
	
}

void CAssetMgr::CreateEngineGraphicShader()
{
	// ǥ�� ���̴� ����
	Ptr<CGraphicShader>	pShader = nullptr;

	// ===========
	// Std2DShader
	// ===========
	pShader = new CGraphicShader;

	pShader->CreateVertexShader(L"HLSL\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"HLSL\\std2d.fx", "PS_Std2D");
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	AddAsset(L"Std2DShader", pShader.Get());


	// =====================
	// Std2DAlphaBlendShader
	// =====================
	pShader = new CGraphicShader;

	pShader->CreateVertexShader(L"HLSL\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"HLSL\\std2d.fx", "PS_Std2D_AlphaBlend");
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);

	AddAsset(L"Std2DAlphaBlendShader", pShader.Get());




}

void CAssetMgr::CreateEngineComputeShader()
{
}

void CAssetMgr::CreateEngineMaterial()
{
	// Std2DMtrl
	Ptr<CMaterial> pMtrl = new CMaterial;
	pMtrl->SetShader(FindAsset<CGraphicShader>(L"Std2DShader"));
	AddAsset(L"Std2DMtrl", pMtrl.Get());
}

void CAssetMgr::CreateEngineSprite()
{
	Ptr<CSprite> pSprite = nullptr;

	Vec2 LeftTopPixel = Vec2(0.f, 520.f);
	Vec2 SlicePixel = Vec2(120.f, 130.f);
	int FrmCount = 10;

	// ������ �ٱ�
	for (int i = 0; i < FrmCount; ++i)
	{
		pSprite = new CSprite;
		pSprite->SetAtlasTex(CAssetMgr::GetInst()->FindAsset<CTexture>(L"Link"));
		if (nullptr == pSprite->GetAtlasTex())
		{
			Ptr<CTexture> pAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"Link", L"Texture\\link.png");
			pSprite->SetAtlasTex(CAssetMgr::GetInst()->FindAsset<CTexture>(L"Link"));
		}
		pSprite->SetLeftTop(LeftTopPixel + Vec2(120.f * i, 0.f));
		pSprite->SetSlice(SlicePixel);
		pSprite->SetBackground(Vec2(300.f, 300.f));

		if (i == 4)
		{
			//pSprite->SetOffset(Vec2(50.f, 0.f));
		}

		wchar_t szName[255] = {};
		swprintf_s(szName, 255, L"LinkSprite_%d", i);

		AddAsset(szName, pSprite.Get());
	}

	// ����
	LeftTopPixel = Vec2(0.f, 650.f);
	for (int i = 0; i < FrmCount; ++i)
	{
		pSprite = new CSprite;
		pSprite->SetAtlasTex(CAssetMgr::GetInst()->FindAsset<CTexture>(L"Link"));
		if (nullptr == pSprite->GetAtlasTex())
		{
			Ptr<CTexture> pAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"Link", L"Texture\\link.png");
			pSprite->SetAtlasTex(CAssetMgr::GetInst()->FindAsset<CTexture>(L"Link"));
		}
		pSprite->SetLeftTop(LeftTopPixel + Vec2(120.f * i, 0.f));
		pSprite->SetSlice(SlicePixel);
		pSprite->SetBackground(Vec2(300.f, 300.f));

		wchar_t szName[255] = {};
		swprintf_s(szName, 255, L"LinkSpriteLeft_%d", i);

		AddAsset(szName, pSprite.Get());
	}

	// ������
	LeftTopPixel = Vec2(0.f, 910.f);
	for (int i = 0; i < FrmCount; ++i)
	{
		pSprite = new CSprite;
		pSprite->SetAtlasTex(CAssetMgr::GetInst()->FindAsset<CTexture>(L"Link"));
		if (nullptr == pSprite->GetAtlasTex())
		{
			Ptr<CTexture> pAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"Link", L"Texture\\link.png");
			pSprite->SetAtlasTex(CAssetMgr::GetInst()->FindAsset<CTexture>(L"Link"));
		}
		pSprite->SetLeftTop(LeftTopPixel + Vec2(120.f * i, 0.f));
		pSprite->SetSlice(SlicePixel);
		pSprite->SetBackground(Vec2(300.f, 300.f));

		wchar_t szName[255] = {};
		swprintf_s(szName, 255, L"LinkSpriteRight_%d", i);

		AddAsset(szName, pSprite.Get());
	}

	Ptr<CFlipbook> pFlipbook = new CFlipbook;
	
	for (int i = 0; i < FrmCount; ++i)
	{
		wchar_t szName[255] = {};
		swprintf_s(szName, 255, L"LinkSprite_%d", i);
		pFlipbook->AddSprite(FindAsset<CSprite>(szName));
	}

	AddAsset(L"LinkFlipbook", pFlipbook.Get());

	Ptr<CFlipbook> pFlipbook1 = new CFlipbook;
	// ����
	for (int i = 0; i < FrmCount; ++i)
	{
		wchar_t szName[255] = {};
		swprintf_s(szName, 255, L"LinkSpriteLeft_%d", i);
		pFlipbook1->AddSprite(FindAsset<CSprite>(szName));
	}

	AddAsset(L"LinkFlipbookLeft", pFlipbook1.Get());

	Ptr<CFlipbook> pFlipbook2 = new CFlipbook;
	// ������
	for (int i = 0; i < FrmCount; ++i)
	{
		wchar_t szName[255] = {};
		swprintf_s(szName, 255, L"LinkSpriteRight_%d", i);
		pFlipbook2->AddSprite(FindAsset<CSprite>(szName));
	}

	AddAsset(L"LinkFlipbookRight", pFlipbook2.Get());

	// Tile Sprite
	Ptr<CTexture> pAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"Tile", L"Texture\\TILE.bmp");

	for (int Row = 0; Row < 6; ++Row)
	{
		for (int Col = 0; Col < 8; ++Col)
		{
			pSprite = new CSprite;
			pSprite->SetAtlasTex(pAtlas);
			pSprite->SetLeftTop(Vec2(Col * 64.f, Row * 64.f));
			pSprite->SetSlice(Vec2(64.f, 64.f));

			// 0 ~ 47 ���� �ڿ� ���ڸ� ���δ�.
			int Idx = Row * 8 + Col;
			wchar_t szName[255] = {};
			swprintf_s(szName, 255, L"TileSprite_%d", Idx);
			AddAsset(szName, pSprite.Get());
		}
	}
}
