#ifndef _STRUCT
#define _STRUCT

// Particle
struct tParticle
{
    float4  LocalPos; // ���� ������Ʈ�� ������ ��� ��ǥ
    float4  WorldPos; // ��ƼŬ�� ���� ��ǥ
    float4  WorldScale; // ��ƼŬ ���� ũ��
    float4  Color; // ��ƼŬ ����

    float4  Force; // ��ƼŬ�� �־����� �ִ� ���� ����
    float4  Velocity; // ��ƼŬ �ӵ�
    float   Mass; // ��ƼŬ ����

    float   Age; // ��ƼŬ ����, Age �� Life �� �����ϸ� ������ ���� ��
    float   Life; // ��ƼŬ �ִ� ����
    float   NormalizedAge; // ��ü ���� ���, ���� Age ����. �ڽ��� Age �� Life ��� ����ȭ �� ��

    int     Active; // ��ƼŬ Ȱ��ȭ ����
    int     padding[3]; // ��ƼŬ ����ü ũ�⸦ 16 ����� ���߱� ���� �е� ����Ʈ
};

// SpawnCount
struct tSpawnCount
{
    int     SpawnCount;
    float3  vPadding;
};





#endif 