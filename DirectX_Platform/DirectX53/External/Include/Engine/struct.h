#pragma once



// Vertex
// 물체의 형태를 이루는 가장 기본 단위
struct Vtx
{	
	Vec3	vPos;		// 정점의 위치
	Vec4	vColor;		// 정점의 색상	
	Vec2	vUV;		// 정점에 입혀질 텍스쳐의 위치(좌표)
};

// DebugShapeInfo
struct tDebugShapeInfo
{
	DEBUG_SHAPE Shape;
	Vec3	    WorldPos;
	Vec3		WorldScale;
	Vec3		WorldRotation;
	Matrix		MatWorld;
	Vec4		Color;
	float		CurTime;
	float		Duration;
	bool		DepthTest;
};

struct tTask
{
	TASK_TYPE Type;
	DWORD_PTR Param0;
	DWORD_PTR Param1;
};


// =============
// Particle 관련
// =============
struct tParticle
{
	Vec4	LocalPos;		// 소유 오브젝트로 부터의 상대 좌표
	Vec4	WorldPos;		// 파티클의 월드 좌표
	Vec4	WorldScale;		// 파티클 월드 크기
	Vec4	Color;			// 파티클 색상

	Vec4	Force;			// 파티클에 주어지고 있는 힘의 총합
	Vec4	Velocity;		// 파티클 속도
	float	Mass;			// 파티클 질량

	float	Age;			// 파티클 나이, Age 가 Life 에 도달하면 수명이 다한 것
	float	Life;			// 파티클 최대 수명
	float	NormalizedAge;  // 전체 수명 대비, 현재 Age 비율. 자신의 Age 를 Life 대비 정규화 한 값

	int		Active;			// 파티클 활성화 여부
	int		padding[3];		// 파티클 구조체 크기를 16 배수로 맞추기 위한 패딩 바이트
};

struct tSpawnCount
{
	int		SpawnCount;
	Vec3	vPadding;
};


// Particle Module
struct tParticleModule
{
	// Spawn
	float	SpawnRate;	// 초당 파티클 생성량
	Vec4	StartColor;	// 초기 파티클 색상
	Vec4	EndColor;	// 파티클 최종 색상
	Vec3	MinScale;	// 생성 시 최소 크기
	Vec3	MaxScale;	// 생성 시 최대 크기

	int		padding;
};








// ===================
// 상수버퍼 연동 구조체
// ===================
struct tTransform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;

	Matrix	matWV;
	Matrix	matWVP;
};
extern tTransform g_Trans;

// 재질을 통해서 전달되는 상수
struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[4];
};

// Global Data
struct tGlobal
{
	Vec2	g_Resolution;
	float   g_DT;
	float   g_EngineDT;
	float   g_AccTime;
	int     g_Light2DCount;
	int     g_Light3DCount;
	int     padding;
};
extern tGlobal g_global;