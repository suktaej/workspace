// WinAPI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WinAPI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL(Standard Annotation Language) : Source code 주석
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 실행된 프로세스의 주소
// window는 가상메모리를 사용
// 동일한 프로세스를 실행시키더라도 동일한 주소를 반환함

                     _In_opt_ HINSTANCE hPrevInstance,  // 이전 실행된 프로세스의 주소(미사용)
                     _In_ LPWSTR    lpCmdLine,          // 문자열 주소 (미사용)
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);     // StringTable(Resource)의 IDS_APP_TITLE에 
                                                                        // 해당하는 값을 읽어와 szTitle에 삽입
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); // 윈도우 정보 등록

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow)) // 윈도우 생성
    {
        return FALSE;
    }

    // 단축키
    // Resource view -> Accelerator Table에서 매칭 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    // 메세지 생성
    MSG msg;

    // Main message loop:
    // GetMessage : message queue가 비어있을 경우 다른 message가 들어올 때 까지 대기
    // msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 메세지 핸들, 단축키 실행 확인
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{   // 구조체 멤버초기화
    WNDCLASSEXW wcex;   

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;  // function pointer : msg의 내용을 처리할 함수
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = szWindowClass;    // Register에 등록되는 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // Window 제공 (선언 되어있고 실행가능, 수정불가)
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   // CreateWindowW(L"KeyName, ...) 첫 인자로 레지스터 이름을 탐색하고 해당 레지스터를 가지고 창을 생성
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

POINT gPos = { 200,200 };
POINT gScale = { 100,100 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // message의 부가인자 (wParam : 키보드 입력 , lParam : 마우스 입력)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:  // 윈도우의 무효화 영역(Invalidate Region)이 발생한 경우
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context(kernel)
            // Device Context : 화면에 그리기를 위해 필요한 데이터의 집합(brush, pen)
            // DC의 목적지는 hWnd
            // 기본 pen은 black, brush는 white

            // DECLARE_HANDLE(HDC);
            // struct __HDC { int unused; }typedef HDC;
            // struct __HWND { int unused; }typedef HWND;
            // 전처리기에 의해 구조체 생성
            // 커널에서 특정 객체의 ID를 받아올 때 중복이 되지 않도록 할 필요가 있음 

            // Pen 생성
			HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            // SelectObject의 반환형은 HGDIOBJ = void*
            // 범용적 함수이므로 반드시 형변환 필요
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);

            // Brush 생성
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0,0,255));
            HBRUSH hHatchBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(0,255,0));

            // GetStockObject : 저장된 오브젝트를 불러오는 함수
            HBRUSH hStockBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
            
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hHatchBrush);
            
            Rectangle(hdc, 10, 10, 100, 100);
            
            // 복원
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 사용이 끝난 오브젝트는 제거
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);
            DeleteObject(hBlueBrush);

            Rectangle(hdc, 
                gPos.x - gScale.x / 2, 
                gPos.y - gScale.y / 2,
                gPos.x + gScale.x / 2,
                gPos.y + gScale.y / 2);
            
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:    // 키 입력 시 동작
    {
        switch (wParam)
        {
		case VK_UP:
            gPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);   // 무효화 영역을 직접 설정(윈도우, 범위, 초기화)
            break;
		case VK_DOWN:
            gPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);   
            break;
        case VK_LEFT:
            gPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);   
            break;
        case VK_RIGHT:
            gPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);   
            break;
        }
    }
    case WM_KEYUP:     // 키 입력 해제 시 동작
    case WM_LBUTTONDOWN:    // 마우스 좌측버튼 입력 시 동작
    {
        POINT p = {};
        // lParam : 마우스 좌표 long type. 2byte, 2byte로 구분
		p.x = LOWORD(lParam); // x좌표
        p.y = HIWORD(lParam); // y좌표
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);    // 특정 프로시저 실행
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
