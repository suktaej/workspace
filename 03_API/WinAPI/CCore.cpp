#include "CCore.h"
#include "pch.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

DEFINITION_SINGLE(CCore);

CObject g_obj;

CCore::CCore()
	: m_hWnd(0), m_ptResolution{}, m_hDC(0)
{
}

CCore::~CCore()
{
	DestroyInst();
	// 종료 시 삭제
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0,0, m_ptResolution.x, m_ptResolution.y };

	// 해상도에 맞게 윈도우 크기 조정
	// AdjustWindowRect : 윈도우 크기를 지정한 해상도로 설정
	// LP : pointer type LPRECT : rect pointer
	// WS_OVERLAPPED : 기본적인 윈도우 형태
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);

	// SetWindowPos : 타이틀바, 메뉴바를 포함한 크기
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DC 생성
	m_hDC = GetDC(m_hWnd);

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	g_obj.Setm_ptPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.Setm_ptScale(Vec2(100, 100));
	
	// Windows의 결과값에 사용하는 변수형(=long)
	HRESULT hr = S_OK;

	return hr; // return E_FAIL;
}

void CCore::progress()
{
	// Draw
	// message의 경우 BeginPaint함수를 사용(message 전용)
	// message와 무관하게 사용하기 위해 Device Context필요
	Update();
	Render();
}

void CCore::Update()
{
	// 변경사항을 모두 갱신 후 고정

	Vec2 vPos = g_obj.Getm_ptPos();

	// GetAsyncKeyState: 비동기 키 입출력(비 message기반)
	// bit 연산 (0x8000 : 눌려있는 상태로 1이면 down, 0이면 up)
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 1;
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 1;
	}

	g_obj.Setm_ptPos(vPos);
}

void CCore::Render()
{
	// Update에서 변경된 내용을 다시 Draw
	Vec2 vPos = g_obj.Getm_ptPos();
	Vec2 vScale = g_obj.Getm_ptScale();

	Rectangle(m_hDC,
		(vPos.x - vScale.x) / 2.f,
		(vPos.y - vScale.y) / 2.f,
		(vPos.x + vScale.x) / 2.f,
		(vPos.y + vScale.y) / 2.f);
}
