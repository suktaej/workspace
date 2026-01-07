#pragma once
class CTimeMgr
{
	DECLARE_SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER	m_llFrequency;

public:
	void init();
	// QueryPerformanceCounter();
};

