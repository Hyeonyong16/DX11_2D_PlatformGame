#include "pch.h"
#include "CLevelMgr.h"

#include "CDevice.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CAssetMgr.h"
#include "CCollisionMgr.h"

#include "CGameObject.h"
#include "components.h"
#include "CPlayerScript.h"
#include "CCameraMoveScript.h"
#include "CPlatformScript.h"

#include "CSetColorCS.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	delete m_CurLevel;
}

void CLevelMgr::Init()
{
	// Level 생성
	m_CurLevel = new CLevel;

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	m_CurLevel->GetLayer(5)->SetName(L"Enermy");
	m_CurLevel->GetLayer(6)->SetName(L"EnermyProjectile");


	// 카메라 역할 오브젝트 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Transform()->SetRelativePos(0.f, 0.f, -100.f);

	pCamObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	//pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetPriority(0); // 메인 카메라로 설정
	pCamObj->Camera()->CheckLayerAll();
	pCamObj->Camera()->CheckLayer(31);

	m_CurLevel->AddGameObject(pCamObj, 0, false);

	// Parent Object
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Parent");

	pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CFlipbookRender);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CRigidbody);
	pObject->AddComponent(new CPlayerScript);

	pObject->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	pObject->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pObject->FlipbookRender()->AddFlipbook(0.f, CAssetMgr::GetInst()->FindAsset<CFlipbook>(L"LinkFlipbook"));

	//pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObject->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pObject->FlipbookRender()->Play(0, 15, true);

	pObject->Collider2D()->SetIndependentScale(true);
	pObject->Collider2D()->SetScale(Vec2(110.f, 110.f));
	pObject->Collider2D()->SetOffset(Vec2(0.f, 0.f));

	//Ptr<CMaterial> pMtrl = pObject->MeshRender()->GetMaterial();
	//pMtrl->SetTexParam(TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"Character", L"Texture\\Character.png"));
	//pMtrl->SetScalarParam(INT_0, 0);

	// Child Object
	/*
	CGameObject* pChild = new CGameObject;
	pChild->SetName(L"Child");
	pChild->AddComponent(new CTransform);
	pChild->AddComponent(new CMeshRender);
	pChild->AddComponent(new CCollider2D);

	pChild->Transform()->SetIndependentScale(true);
	pChild->Transform()->SetRelativePos(150.f, 0.f, 0.f);
	pChild->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pChild->Collider2D()->SetNotifyParent(true);
	pChild->Collider2D()->SetOffset(Vec2(0.f, 0.f));
	pChild->Collider2D()->SetScale(Vec2(1.1f, 1.1f));

	pChild->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
	pChild->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	
	// 부모 자식 연결
	pObject->AddChild(pChild);
	*/

	// 레벨에 부모 오브젝트만 추가
	m_CurLevel->AddGameObject(pObject, 3, true);

	//// ========
	//// Particle
	//// ========
	/*
	pObject = new CGameObject;
	pObject->SetName(L"Particle");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CParticleRender);		

	pObject->Transform()->SetRelativePos(0.f, 300.f, 100.f);
	pObject->Transform()->SetRelativeScale(300.f, 300.f, 1.f);

	pObject->ParticleRender()->SetSpawnRate(1.f);

	
	// 오브젝트를 0번 레이어에 추가
	m_CurLevel->AddGameObject(pObject, 0, false);
	*/

	CGameObject* pPlatform = new CGameObject;
	pPlatform->SetName(L"Platform");

	pPlatform->AddComponent(new CTransform);
	pPlatform->AddComponent(new CCollider2D);
	pPlatform->AddComponent(new CPlatformScript);

	pPlatform->Transform()->SetRelativePos(0.f, -300.0f, 100.f);
	pPlatform->Transform()->SetRelativeScale(600.f, 100.f, 1.f);

	pPlatform->Collider2D()->SetIndependentScale(false);

	m_CurLevel->AddGameObject(pPlatform, 7, true);

	// Level 에 넣을 GameObject 생성
	//pObject = new CGameObject;
	//pObject->SetName(L"Monster");
	//pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CFlipbookRender);
	//pObject->AddComponent(new CCollider2D);

	//pObject->Transform()->SetRelativePos(0.f, 300.f, 100.f);
	//pObject->Transform()->SetRelativeScale(300.f, 300.f, 1.f);

	//pObject->FlipbookRender()->AddFlipbook(0, CAssetMgr::GetInst()->FindAsset<CFlipbook>(L"LinkFlipbook"));
	////pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	////pObject->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	//pObject->FlipbookRender()->Play(0, 15, true);

	//// 오브젝트를 0번 레이어에 추가
	//m_CurLevel->AddGameObject(pObject, 5, false);


	// 충돌 레이어 지정
	CCollisionMgr::GetInst()->CollisionLayerCheck(3, 5);
	CCollisionMgr::GetInst()->CollisionLayerCheck(4, 5);
	CCollisionMgr::GetInst()->CollisionLayerCheck(3, 6);
	CCollisionMgr::GetInst()->CollisionLayerCheck(3, 7);

	// 레벨 시작
	m_CurLevel->Begin();
}

void CLevelMgr::Progress()
{
	// =====
	// Tick
	// =====
	m_CurLevel->Tick();

	m_CurLevel->Deregister();

	m_CurLevel->FinalTick();
}