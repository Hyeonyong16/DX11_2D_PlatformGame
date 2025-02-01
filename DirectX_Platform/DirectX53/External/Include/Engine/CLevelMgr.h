#pragma once


class CLevelMgr
	: public singleton<CLevelMgr>
{
	SINGLE(CLevelMgr);
private:
	class CLevel*	m_CurLevel;

public:
	CLevel* GetCurrentLevel() { return m_CurLevel; }

public:
	void Init();
	void Progress();
};

