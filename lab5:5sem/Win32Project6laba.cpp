// Win32Project6laba.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project6laba.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];           


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


INT color = 0;
INT shape = 0;
INT draw = 0;
INT my_message;

HWND radiob_colors;
HWND radiob_shape;
HWND check_box;

const UINT win_mess = RegisterWindowMessage(L"geraffe");


void make_my_message() {
	my_message = 0;
	my_message = my_message + color * 100;
	my_message = my_message + shape * 10;
	my_message = my_message + draw;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

 
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT6LABA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT6LABA));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT6LABA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT6LABA);
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
	case WM_GETMINMAXINFO: 
	{
		MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
		POINT Min = { 300, 500 };
		POINT  Max = { 300, 500 };
		pInfo->ptMinTrackSize = Min;
		pInfo->ptMaxTrackSize = Max;
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_DRAW:
			if (!IsDlgButtonChecked(hWnd, IDC_DRAW)) {
				CheckDlgButton(hWnd, IDC_DRAW, BST_CHECKED);
			}
			else {
				CheckDlgButton(hWnd, IDC_DRAW, BST_UNCHECKED);
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
	{
		SetTimer(hWnd, IDT_TIMER, 100, NULL);
		radiob_colors = CreateWindow(L"BUTTON", L"Choose a color:", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 50, 50, 150, 100, hWnd, NULL, hInst, NULL);
		CreateWindow(L"BUTTON", L"Red", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 15, 80, 20, radiob_colors, (HMENU)IDC_RED, hInst, NULL);
		CreateWindow(L"BUTTON", L"Green", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 40, 80, 20, radiob_colors, (HMENU)IDC_GREEN, hInst, NULL);
		CreateWindow(L"BUTTON", L"Blue", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 65, 80, 20, radiob_colors, (HMENU)IDC_BLUE, hInst, NULL);

		radiob_shape = CreateWindow(L"BUTTON", L"Choose a shape:", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 50, 200, 150, 115, hWnd, NULL, hInst, NULL);
		CreateWindow(L"BUTTON", L"Rhomb", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 15, 80, 20, radiob_shape, (HMENU)IDC_RHOMB, hInst, NULL);
		CreateWindow(L"BUTTON", L"Square", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 40, 80, 20, radiob_shape, (HMENU)IDC_SQUARE, hInst, NULL);
		CreateWindow(L"BUTTON", L"Circle", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 65, 80, 20, radiob_shape, (HMENU)IDC_CIRCLE, hInst, NULL);
		CreateWindow(L"BUTTON", L"Star", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 90, 80, 20, radiob_shape, (HMENU)IDC_STAR, hInst, NULL);

		check_box = CreateWindow(L"BUTTON", L"Draw", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 50, 350, 70, 30, hWnd, (HMENU)IDC_DRAW, hInst, NULL);

		break;
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
		case IDT_TIMER:
		{
			if (IsDlgButtonChecked(radiob_colors, IDC_RED) == BST_CHECKED) {
				color = 1;
			}
			if (IsDlgButtonChecked(radiob_colors, IDC_GREEN) == BST_CHECKED) {
				color = 2;
			}
			if (IsDlgButtonChecked(radiob_colors, IDC_BLUE) == BST_CHECKED) {
				color = 3;
			}


			if (IsDlgButtonChecked(radiob_shape, IDC_RHOMB) == BST_CHECKED) {
				shape = 1;
			}
			if (IsDlgButtonChecked(radiob_shape, IDC_SQUARE) == BST_CHECKED) {
				shape = 2;
			}
			if (IsDlgButtonChecked(radiob_shape, IDC_CIRCLE) == BST_CHECKED) {
				shape = 3;
			}
			if (IsDlgButtonChecked(radiob_shape, IDC_STAR) == BST_CHECKED) {
				shape = 4;
			}


			if (SendMessage(check_box, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				draw = 1;
			}
			else {
				draw = 2;
			}
			
			if (color == 0) {
				CheckDlgButton(radiob_colors, IDC_RED, BST_CHECKED);
				color = 1;
			}
			if (shape == 0) {
				CheckDlgButton(radiob_shape, IDC_RHOMB, BST_CHECKED);
				shape = 1;
			}
			make_my_message();
			HWND window2 = FindWindow(NULL, L"part2");
			if (window2 != NULL) {
				SendMessage(window2, win_mess, (WPARAM)my_message, NULL);
			}
		}
		break;
		default:
			break;
		}
	}
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
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
	}
