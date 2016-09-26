// Win32Project5.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project5.h"
#include <string>
#include <vector>
#include <iostream>

#define MAX_LOADSTRING 100

using namespace std;

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int x_cursor;
int y_cursor;

int x_cur = 200;
int y_cur = 100; 


vector<int> x;
vector<int> y;

HANDLE H1;
HANDLE H2;
HANDLE H3;
HANDLE H4;

HANDLE H1_L;
HANDLE H2_L;
HANDLE H3_L;
HANDLE H4_L;

HDC M;

int k = 12;
bool isR;

void draw_bmp(HDC hdc, int x1, int y1, bool isR) {
	if (isR) {
		if (x_cur != x1 || y_cur != y1) {
			if (k > 9) {
				k--;
				SelectObject(M, H1);
			}
			if (k > 6 && k <= 9) {
				k--;
				SelectObject(M, H2);
			}
			if (k > 3 && k <= 6) {
				k--;
				SelectObject(M, H3);
			}
			if (k > 0 && k <= 3) {
				k--;
				SelectObject(M, H4);
			}
			if (k == 0) {
				k = 9;
			}
		}
	}
	else {
		if (x_cur != x1 || y_cur != y1) {
			if (k > 9) {
				k--;
				SelectObject(M, H1_L);
			}
			if (k > 6 && k <= 9) {
				k--;
				SelectObject(M, H2_L);
			}
			if (k > 3 && k <= 6) {
				k--;
				SelectObject(M, H3_L);
			}
			if (k > 0 && k <= 3) {
				k--;
				SelectObject(M, H4_L);
			}
			if (k == 0) {
				k = 9;
			}
		}
	}
	BitBlt(hdc, x1, y1, 50, 50, M, 0, 0, SRCCOPY);
}

void make_path(int x1, int y1) {
	x.clear();
	y.clear();
	int tcur_x = x_cur;
	int tcur_y = y_cur;

	while ((tcur_x != x1) || (tcur_y != y1)) {
		if (tcur_x > x1) {
			tcur_x--;
		}
		if (tcur_x < x1) {
			tcur_x++;
		}

		if (tcur_y > y1) {
			tcur_y--;
		}
		if (tcur_y < y1) {
			tcur_y++;
		}
		x.push_back(tcur_x);
		y.push_back(tcur_y);
	}
	reverse(x.begin(), x.end());
	reverse(y.begin(), y.end());
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT5));

    MSG msg;

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT5);
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
	case WM_LBUTTONDOWN:
	{
		x_cursor = LOWORD(lParam);
		y_cursor = HIWORD(lParam);
		make_path(x_cursor, y_cursor);
	}
	break;
	case WM_CREATE: {
		x.push_back(x_cur);
		y.push_back(y_cur);
		SetTimer(hWnd, IDT_TIMER1, 50, (TIMERPROC)NULL);

		HDC hdc = GetDC(hWnd);
		M = CreateCompatibleDC(hdc);
		H1 = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		SelectObject(M, H1);
		H2 = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		H3 = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		H4 = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly4.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
		H1_L = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly1_l.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		H2_L = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly2_l.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		H3_L = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly3_l.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		H4_L = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Ekaterina\\Documents\\fly4_l.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			int tcur_x = x_cur;
			int tcur_y = y_cur;
			if (x.size() != 0 && y.size() != 0) {
				tcur_x = x.back();
				tcur_y = y.back();
				x.pop_back();
				y.pop_back();
			}
			if (tcur_x > x_cur) {
				isR = true;
			}
			else {
				isR = false;
			}
			draw_bmp(hdc, tcur_x, tcur_y, isR);
			x_cur = tcur_x;
			y_cur = tcur_y;
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
	{
		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
	}
	break;
    case WM_DESTROY:
		KillTimer(hWnd, IDT_TIMER1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


