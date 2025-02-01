#include "pch.h"
#include "CFlipbook.h"


CFlipbook::CFlipbook()
    : CAsset(ASSET_TYPE::FLIPBOOK)
{
}

CFlipbook::~CFlipbook()
{
}


int CFlipbook::Save(const wstring& _FilePath)
{
    return 0;
}

int CFlipbook::Load(const wstring& _FilePath)
{
    return 0;
}
