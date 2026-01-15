#pragma once
#include <vector>
// frame 동기화 및 키 상태 확인

enum class EKEY_TYPE
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	Q,
	W,
	E,
	R,
	A,
	S,
	D,
	F,
	ALT,
	CTRL,
	LSHIFT,
	ENTER,
	ESC,
	LAST
};

enum class EKEY_STATE
{
	DOWN,
	HOLD,
	UP,
	NONE
};

struct FKeyInfo
{
	EKEY_STATE eState;
	bool bPrev;	// 이전 frame의 key down 여부
};

extern int g_arrVK[(int)EKEY_TYPE::LAST];

class CKeyMgr
{
	DECLARE_SINGLE(CKeyMgr);

private:
	std::vector<FKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	EKEY_STATE GetKeyState(EKEY_TYPE _eKey) { return m_vecKey[(int)_eKey].eState; }
};
