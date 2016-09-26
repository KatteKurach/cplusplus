// Win32Project4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project4.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
LPDRAWITEMSTRUCT display;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND btn1;
HWND btn2;
POINT pt[3];
RECT rc;

VOID draw(HDC d) {
	HBRUSH dr = CreateSolidBrush((COLORREF)RGB(156, 117, 128));

	(HBRUSH)SelectObject(d, dr);
	Rectangle(d, 380, 370, 400, 440); 
	Rectangle(d, 420, 370, 440, 440);
	Rectangle(d, 400, 230, 420, 260);

	POINT pt[6];

	pt[0].x = 360;
	pt[0].y = 280;
	pt[1].x = 340;
	pt[1].y = 295;
	pt[2].x = 326;
	pt[2].y = 275;
	
	pt[3].x = 312;
	pt[3].y = 275;
	pt[4].x = 340;
	pt[4].y = 309;
	pt[5].x = 360;
	pt[5].y = 294;
	Polygon(d, pt, 6); //hand

	pt[0].x = 460;
	pt[0].y = 280;
	pt[1].x = 490;
	pt[1].y = 295;
	pt[2].x = 470;
	pt[2].y = 320;

	pt[3].x = 456;
	pt[3].y = 320;
	pt[4].x = 478;
	pt[4].y = 297;
	pt[5].x = 460;
	pt[5].y = 294;
 	Polygon(d, pt, 6); //hand
	
	dr = CreateSolidBrush((COLORREF)RGB(255, 232, 17));
	(HBRUSH)SelectObject(d, dr);
	Ellipse(d, 355, 195, 375, 210); //lampa
	Ellipse(d, 445, 195, 465, 210); //lampa
	Ellipse(d, 476, 290, 491, 305); //hand
	Ellipse(d, 332, 293, 349, 310); //hand
	dr = CreateSolidBrush((COLORREF)RGB(255, 144, 17));
	(HBRUSH)SelectObject(d, dr);
	Ellipse(d, 405, 170, 419, 190); //lampa


	dr = CreateSolidBrush((COLORREF)RGB(86, 231, 173));
	(HBRUSH)SelectObject(d, dr);
	Rectangle(d, 360, 250, 460, 380); //body
	Rectangle(d, 370, 180, 450, 240); //head

	dr = CreateSolidBrush((COLORREF)RGB(0, 128, 255));
	(HBRUSH)SelectObject(d, dr);
	Ellipse(d, 370, 252, 386, 268);
	Ellipse(d, 370, 270, 386, 286);
	Ellipse(d, 370, 288, 386, 304);
	Ellipse(d, 370, 306, 386, 322);
	Ellipse(d, 370, 324, 386, 340);
	Ellipse(d, 370, 342, 386, 358);
	Ellipse(d, 370, 360, 386, 376);

	Rectangle(d, 400, 262, 452, 272);
	Rectangle(d, 400, 277, 452, 287);

	dr = CreateSolidBrush((COLORREF)RGB(0, 0, 0));
	(HBRUSH)SelectObject(d, dr);
	MoveToEx(d, 385, 192, NULL);
	LineTo(d, 397, 185);
	MoveToEx(d, 425, 192, NULL);
	LineTo(d, 437, 192);
	Ellipse(d, 385, 195, 397, 210); //eye
	Ellipse(d, 425, 195, 437, 210); //eye
	Arc(d, 391, 210, 431, 230, 391, 220, 431, 220); //smile
	Arc(d, 387, 205, 434, 225, 391, 220, 431, 220);

	//Rectangle(d, 406, 210, 416, 220);
	//Arc(d, 391, 210, 411, 230, 391, 220, 411, 220);
	//Arc(d, 411, 210, 431, 230, 411, 220, 431, 220);

	Pie(d, 375, 430, 405, 450, 405, 440, 375, 440); //boot
	Pie(d, 415, 430, 445, 450, 445, 440, 415, 440); //boot

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
    LoadStringW(hInstance, IDC_WIN32PROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT4));

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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
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
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDL_BUTTON1:
				draw(GetDC(hWnd));
				break;
			case IDL_BUTTON2:
				RECT clear_zone;
				clear_zone = { 0, 0, 1300, 1300 };
				InvalidateRect(hWnd, &clear_zone, true);
				UpdateWindow(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
		//	draw(GetDC(hWnd));
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:
		btn1 = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 0, 0, 60, 60, hWnd, (HMENU)IDL_BUTTON1, NULL, NULL);
		btn2 = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 70, 0, 60, 60, hWnd, (HMENU)IDL_BUTTON2, NULL, NULL);
		break;
	case WM_DRAWITEM:
		display = (LPDRAWITEMSTRUCT) lParam;
		switch (display->CtlID) {
			case IDL_BUTTON1: {
				POINT pt[3];
				HGDIOBJ hbrushOld;
				HBRUSH dr = CreateSolidBrush(COLORREF(RGB(255, 252, 28)));

				hbrushOld = (HBRUSH)SelectObject(display->hDC, dr);
				Ellipse(display -> hDC, 10, 10, 50, 50);

				dr = CreateSolidBrush(COLORREF(RGB(77, 255, 125)));
				hbrushOld = (HBRUSH)SelectObject(display->hDC, dr);
				pt[0].x = 30;
				pt[0].y = 17;
				pt[1].x = 20;
				pt[1].y = 40;
				pt[2].x = 40;
				pt[2].y = 40;
				Polygon(display->hDC, pt, 3);
			}
			break;
			case IDL_BUTTON2: {
				POINT pt[3];
				HGDIOBJ hbrushOld;
				HBRUSH dr = CreateSolidBrush(COLORREF(RGB(255, 252, 28)));

				hbrushOld = (HBRUSH)SelectObject(display->hDC, dr);
				Ellipse(display->hDC, 10, 10, 50, 50);

				dr = CreateSolidBrush(COLORREF(RGB(255, 77, 125)));
				hbrushOld = (HBRUSH)SelectObject(display->hDC, dr);
				pt[0].x = 30;
				pt[0].y = 40;
				pt[1].x = 20;
				pt[1].y = 17;
				pt[2].x = 40;
				pt[2].y = 17;
				Polygon(display->hDC, pt, 3);
			}
			break;
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
