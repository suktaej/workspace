//#include "framework.h"
//#include "DX.h"

#include <windows.h>

// main window의 handle
// 생성된 창을 식별하는 용도
HWND ghMainWnd = 0;

// window applcation program instance에 필요한 코드들의 wrapping function
// initialize 성공 시 true 반환
bool InitWindowsApp(HINSTANCE instanceHandle, int show);

// message loop code function
int Run();

// main windows가 받은 event를 처리하는 window procedure function
LRESULT CALLBACK WndProc(HWND hWnd, UINT  msg, WPARAM wParam, LPARAM lParam);

// Entry point 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, PSTR pCmdLine, int nShowCmd)
{
	// main window 초기화 진행
	if (!InitWindowsApp(hInstance, nShowCmd))
		return 0;

	// 초기화에 성공 시 message loop로 진행
	// loop는 종료(WM_QUIT) message를 받을 때 까지 반복
	return Run();
}

bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{
	// 창을 생성할 떄 가장먼저 창의 특성을 서술
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;  // function pointer : msg의 내용을 처리할 함수
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instanceHandle;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"BasicWndClass";

	// WNDCLASS instance를 windows에 등록
	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	// Register에 등록했다면 CreateWindow로 창을 생성
	// 해당 함수는 생성된 창의 handle을 반환 (생성 실패시 0)

	ghMainWnd = CreateWindowW(
		L"BasicWndClass",	// 사용할 window class 이름
		L"Win32Basic",		// 창의 제목
		WS_OVERLAPPEDWINDOW,// style flags
		CW_USEDEFAULT,		// x 좌표
		CW_USEDEFAULT,		// y 좌표
		CW_USEDEFAULT,		// 너비
		CW_USEDEFAULT,		// 높이
		0,					// 부모 창
		0,					// 메뉴 핸들
		instanceHandle,		// 응용 프로그램 인스턴스
		0);					// 추가적인 생성 플래그

	if (ghMainWnd == 0)
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		return false;
	}

	// window 생성 성공 시 이를 화면에 표시
	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

int Run()
{
	MSG msg = { 0 };
	
	BOOL bRet = 1;
	// GetMessage()는 message recv에 오류가 있으면 -1을 반환
	// 또한 호출 시, message가 도달할 때 까지 응용 프로세스의 thread가 sleep상태로 전환
	while ((bRet = GetMessage(&msg, 0, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			MessageBox(0, L"GetMessage FAILED", L"Error", MB_OK);
			break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT  msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello world", L"Hello", MB_OK);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// 명시적으로 처리하지 않은 다른 message들은 default window procedure에게 전달
	// 현재 window procdeure는 반드시 DefWindowProc의 반환값을 돌려주어야함
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
