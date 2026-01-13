#pragma once
#include "define.h"

class CCore
{
	DECLARE_SINGLE(CCore);

	HWND m_hWnd;	// 메인 윈도우 핸들
	POINT m_ptResolution;	// 메인 윈도우 해상도
	HDC m_hDC;	// 메인 윈도우 Draw용 DC

	HBITMAP m_hBit;
	HDC m_memDC;

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();
	
private:
	void Update();
	void Render();

public:
	HWND GetMainhWnd() { return m_hWnd; }

};
