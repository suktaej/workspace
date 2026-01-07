#include "CCore.h"
#include "pch.h"

CCore* CCore::inst = nullptr;

CCore::CCore()
{
}

CCore::~CCore()
{
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	mhWnd = _hWnd;
	mPtResolution = _ptResolution;
	// Windows의 결과값에 사용하는 변수형(=long)
	HRESULT hr = S_OK;

	// return E_FAIL;
	return hr;
}

void CCore::progress()
{
}
