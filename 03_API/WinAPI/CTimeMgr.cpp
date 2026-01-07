#include "pch.h"
#include "CTimeMgr.h"

DEFINITION_SINGLE(CTimeMgr);
// 1s 후의 이동거리 = speed * DeltaTime
// DeltaTime = 1/FPS
// 매 frame이 변동되는 시간이 다르므로 지난 frame부터 지금 frame까지 걸린시간을 사용

CTimeMgr::CTimeMgr()
	:m_llCurCount{}
{
};

CTimeMgr::~CTimeMgr()
{
	DestroyInst();
};

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceFrequency(&m_llFrequency);
}
