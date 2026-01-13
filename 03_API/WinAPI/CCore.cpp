#include "CCore.h"
#include "pch.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

DEFINITION_SINGLE(CCore);

CObject g_obj;

CCore::CCore()
	: m_hWnd(0), m_ptResolution{}, m_hDC(0), m_hBit(0), m_memDC(0)
{
}

CCore::~CCore()
{
	DestroyInst();
	// 종료 시 삭제
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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

	// DC 생성 : window(HWND)가 가지고 있는 bitmap을 device context의 목표로 할당
	m_hDC = GetDC(m_hWnd);

	// Dubble buffering 용도의 bitmap과 DC생성
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
	
	// 새로 생성한 bitmap과 dc를 연결
	// DC 생성 시 최소한의 정보로 1pixel의 목적지 bitmap이 생성되어 있으므로 이 정보를 삭제
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

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
	// Manager Update
	CTimeMgr::GetInst()->update();

	// message의 경우 BeginPaint함수를 사용(message 전용)
	// message와 무관하게 사용하기 위해 Device Context필요
	Update();
	Render();
}

void CCore::Update()
{
	// 변경사항을 모두 갱신 후 고정
	Vec2 vPos = g_obj.Getm_ptPos();
	constexpr float SPEED = 300.f;

	// GetAsyncKeyState: 비동기 키 입출력(비 message기반)
	// bit 연산 (0x8000 : 눌려있는 상태로 1이면 down, 0이면 up)
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= SPEED * CTimeMgr::GetInst()->GetFDT();
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += SPEED * CTimeMgr::GetInst()->GetFDT();
	}

	g_obj.Setm_ptPos(vPos);
}

void CCore::Render()
{
	// 매 프레임마다 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x, m_ptResolution.y);

	// Update에서 변경된 내용을 다시 Draw
	Vec2 vPos = g_obj.Getm_ptPos();
	Vec2 vScale = g_obj.Getm_ptScale();

	Rectangle(m_memDC,
		(vPos.x - vScale.x) / 2.f,
		(vPos.y - vScale.y) / 2.f,
		(vPos.x + vScale.x) / 2.f,
		(vPos.y + vScale.y) / 2.f);

	// BitBlt : double buffering 사용 시 bit맵을 이전하는 함수
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, 
			m_memDC, 0, 0, SRCCOPY);
}
