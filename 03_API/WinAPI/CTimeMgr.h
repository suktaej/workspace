#pragma once
class CTimeMgr
{
	DECLARE_SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	double m_deltaTime; // frame간의 시간 값
	double m_Acc;
	UINT m_iCallCount;	// 함수호출 회수 체크
	UINT m_iFPS;

public:
	void init();
	void update();
	// QueryPerformanceCounter();

public:
	double GetDT() { return m_deltaTime; }
	float GetFDT() { return (float)m_deltaTime; }
};

