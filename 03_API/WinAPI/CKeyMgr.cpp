#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)EKEY_TYPE::LAST] =
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,
	'Q',
	'W',
	'E',
	'R',
	'A',
	'S',
	'D',
	'F',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_RETURN,
	VK_ESCAPE,
};

DEFINITION_SINGLE(CKeyMgr);

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)EKEY_TYPE::LAST; ++i)
		m_vecKey.push_back(FKeyInfo{ EKEY_STATE::NONE, false });

	m_vecKey[(int)EKEY_TYPE::LEFT];
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기
	// main window(hMainWhd)만 keyMgr이 동작하게 하고 싶다면 focus된 window와 동일한지 확인
	// HWND hMainWnd = CCore::GetInst()->GetMainhWnd();
	
	// 반환 값이 null이라면 어떤 윈도우도 선택된 상태가 아님
	HWND hWnd = GetFocus();

	// 포커싱 중일 때
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)EKEY_TYPE::LAST; ++i)
		{
			// GetAsyncKeyState: 비동기 키 입출력(비 message기반)
			// bit 연산 (0x8000 : 눌려있는 상태로 1이면 down, 0이면 up)
			// 키가 눌려있다
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				// 이전 frame에 눌려있었다면
				if (m_vecKey[i].bPrev)
					m_vecKey[i].eState = EKEY_STATE::HOLD;
				// 눌리지 않았다
				else
					m_vecKey[i].eState = EKEY_STATE::DOWN;

				m_vecKey[i].bPrev = true;
			}
			else
			{
				if (m_vecKey[i].bPrev)
					m_vecKey[i].eState = EKEY_STATE::UP;
				else
					m_vecKey[i].eState = EKEY_STATE::NONE;

				m_vecKey[i].bPrev = false;
			}
		}
	}
	// 포커싱 해제 시
	else
	{
		for (int i = 0; i < (int)EKEY_TYPE::LAST; ++i)
		{
			m_vecKey[i].bPrev = false;
			
			if (EKEY_STATE::DOWN == m_vecKey[i].eState || EKEY_STATE::HOLD == m_vecKey[i].eState)
				m_vecKey[i].eState = EKEY_STATE::UP;
			else if (EKEY_STATE::UP == m_vecKey[i].eState)
				m_vecKey[i].eState = EKEY_STATE::NONE;
		}
	}
}
