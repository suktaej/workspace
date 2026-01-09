#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"

DEFINITION_SINGLE(CTimeMgr);
// 1s 후의 이동거리 = speed * DeltaTime
// DeltaTime = 1/FPS
// 매 frame이 변동되는 시간이 다르므로 지난 frame부터 지금 frame까지 걸린시간을 사용

CTimeMgr::CTimeMgr()
	:m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_deltaTime(0.)
	, m_Acc(0.)
	, m_iCallCount(0)
{
};

CTimeMgr::~CTimeMgr()
{
	DestroyInst();
};

void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);
	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	// 1 frame update되는 시간을 도출
	QueryPerformanceCounter(&m_llCurCount);
	// 이전 frame counting과 현재 frame counting 값의 차이를 도출
	// frequency는 초당 count 수이므로 이를 나누면 실제 시간 도출
	m_deltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	// 1/deltaTime = frame

	// 이전 카운트 값을 현재 값으로 갱신
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;

	// deltaTime 누적
	m_Acc += m_deltaTime;

	// 1초 확인
	if (m_Acc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_Acc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_deltaTime);

		SetWindowText(CCore::GetInst()->GetMainhWnd(), szBuffer);
	}
}
