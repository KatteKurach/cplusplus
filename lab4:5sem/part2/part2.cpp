// part2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "part2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


INT color;
INT shape;
INT draw;
INT my_message;

UINT win_mess = RegisterWindowMessage(L"geraffe");

int x_cursor;
int y_cursor;

void parse_my_message() {
	color = my_message / 100;
	shape = (my_message % 100) / 10;
	draw = my_message % 10;
}

void set_my_brush(HDC hdc) {
	HBRUSH hBrush;
	if (color == 1) {
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
	}
	if (color == 2) {
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
	} 
	if (color == 3){
		hBrush = CreateSolidBrush(RGB(51, 153, 255));
	}
	SelectObject(hdc, hBrush);
}


void draw_rhomb(HDC hdc) {
	POINT pt[4];
	pt[0].x = x_cursor;
	pt[0].y = y_cursor - 50;
	pt[1].x = x_cursor + 30;
	pt[1].y = y_cursor;
	pt[2].x = x_cursor;
	pt[2].y = y_cursor + 50;
	pt[3].x = x_cursor - 30;
	pt[3].y = y_cursor;
	Polygon(hdc, pt, 4);
}

void draw_square(HDC hdc) {
	Rectangle(hdc, x_cursor - 50, y_cursor - 50, x_cursor + 50, y_cursor + 50);
}

void draw_circle(HDC hdc) {
	Ellipse(hdc, x_cursor - 50, y_cursor - 50, x_cursor + 50, y_cursor + 50);
}

void draw_star(HDC hdc) {
	POINT pt[10];
	
	pt[0].x = x_cursor;
	pt[0].y = y_cursor - 60;
	pt[1].x = x_cursor + 20;
	pt[1].y = y_cursor - 20;
	pt[2].x = x_cursor + 60;
	pt[2].y = y_cursor - 20;
	pt[3].x = x_cursor + 22;
	pt[3].y = y_cursor;
	pt[4].x = x_cursor + 40;
	pt[4].y = y_cursor + 40;
	pt[5].x = x_cursor;
	pt[5].y = y_cursor + 20;

	pt[6].x = x_cursor - 40;
	pt[6].y = y_cursor + 40;
	pt[7].x = x_cursor - 22;
	pt[7].y = y_cursor;
	pt[8].x = x_cursor - 60;
	pt[8].y = y_cursor - 20;
	pt[9].x = x_cursor - 20;
	pt[9].y = y_cursor - 20;
	Polygon(hdc, pt, 10);
}


void draw_picture(HDC hdc) {
	set_my_brush(hdc);
	if (shape == 1) {
		draw_rhomb(hdc);
	}
	if (shape == 2) {
		draw_square(hdc);
	}
	if (shape == 3) {
		draw_circle(hdc);
	}
	if (shape == 4) {
		draw_star(hdc);
	}
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PART2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PART2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PART2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PART2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

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
	case WM_CREATE:
		SetWindowText(hWnd, L"part2");
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
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
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
		POINT Min = { 600, 600 };
		POINT  Max = { 600, 600 };
		pInfo->ptMinTrackSize = Min;
		pInfo->ptMaxTrackSize = Max;
		break;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		x_cursor = LOWORD(lParam);
		y_cursor = HIWORD(lParam);

		parse_my_message();
		if (draw == 1) {
			draw_picture(hdc);
		}
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
		PostQuitMessage(0);
		break;
	default:
		if (win_mess == message) {
			my_message = (int)wParam;
		}
		else {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
    return 0;
}
