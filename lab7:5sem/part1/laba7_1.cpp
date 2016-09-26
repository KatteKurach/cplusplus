// laba7_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "laba7_1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                
WCHAR szWindowClass[MAX_LOADSTRING];            

struct MyStruct {
	int dx;
	HDC hdc;

	MyStruct() {}
};

HANDLE h_thread1;
HANDLE h_thread2;
HANDLE h_mutex;

HBRUSH hBrush_red = CreateSolidBrush((COLORREF)RGB(62, 225, 149));;
HBRUSH hBrush_white = CreateSolidBrush((COLORREF)RGB(255, 255, 255));

HPEN white_pen = CreatePen(BS_SOLID, 1, RGB(255, 255, 255));
HPEN black_pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));

int cur_x = 400;
int cur_y = 50;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void draw_star(HDC hdc, int x, int y) {
	POINT pt[10];

	pt[0].x = x;
	pt[0].y = y - 60;
	pt[1].x = x + 20;
	pt[1].y = y - 20;
	pt[2].x = x + 60;
	pt[2].y = y - 20;
	pt[3].x = x + 22;
	pt[3].y = y;
	pt[4].x = x + 40;
	pt[4].y = y + 40;
	pt[5].x = x;
	pt[5].y = y + 20;

	pt[6].x = x - 40;
	pt[6].y = y + 40;
	pt[7].x = x - 22;
	pt[7].y = y;
	pt[8].x = x - 60;
	pt[8].y = y - 20;
	pt[9].x = x - 20;
	pt[9].y = y - 20;
	Polygon(hdc, pt, 10);
}


DWORD WINAPI draw(LPVOID lpParam)
{
	HDC hdc = ((MyStruct*)lpParam)->hdc;
	int dx = ((MyStruct*)lpParam)->dx;
	int dy = 5;

	while(true){
		WaitForSingleObject(h_mutex, INFINITE);
		(HBRUSH)SelectObject(hdc, hBrush_white);
		SelectObject(hdc, white_pen);
		draw_star(hdc, cur_x, cur_y);

		cur_x += dx;
		cur_y += dy;


		(HBRUSH)SelectObject(hdc, hBrush_red);
		SelectObject(hdc, black_pen);
		draw_star(hdc, cur_x, cur_y);
		Sleep(150);
		ReleaseMutex(h_mutex);
	}
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

  
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LABA7_1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA7_1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA7_1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA7_1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
	{
		h_mutex = CreateMutex(NULL, FALSE, NULL);

		MyStruct *param1 = (MyStruct *)new MyStruct();
		param1->dx = 50;
		param1->hdc = GetDC(hWnd);

		MyStruct *param2 = (MyStruct *)new MyStruct();;
		param2->dx = -55;
		param2->hdc = GetDC(hWnd);

		h_thread1 = CreateThread(NULL, 0, draw, param1, 0, NULL);
		h_thread2 = CreateThread(NULL, 0, draw, param2, 0, NULL);
	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		TerminateThread(h_thread1, 0);
		TerminateThread(h_thread2, 0);
		CloseHandle(h_thread1);
		CloseHandle(h_thread2);
		CloseHandle(h_mutex);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

