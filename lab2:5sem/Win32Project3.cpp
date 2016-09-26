// Win32Project3.cpp : Defines the entry point for the application.
//

#include <stdio.h>
#include "stdafx.h"
#include "Win32Project3.h"


#define MAX_LOADSTRING 100

// Global Variables:
HWND hListbox1;
HWND hListbox2;
HWND hEdit;

HINSTANCE hInst;              // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR mystr[1024];
WCHAR array[15];

int isSelected;
int count1;
int count2;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_WIN32PROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT3);
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
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDL_BUTTON_ADD:
				GetWindowText(hEdit, mystr, 1024);
				if ((int)SendMessage(hListbox1, LB_FINDSTRINGEXACT, NULL, (LPARAM)mystr) == LB_ERR) {
					SendMessage(hListbox1, LB_ADDSTRING, NULL, LPARAM(mystr));
				}
				break;
			case IDL_BUTTON_TORIGHT:
				LPWSTR temp[1024];
				isSelected = (int) SendMessage(hListbox1, LB_GETCURSEL, NULL, NULL);
				if (isSelected != -1) {
					SendMessage(hListbox1, LB_GETTEXT, (WPARAM)isSelected, (LPARAM)temp);
					if ((int)SendMessage(hListbox2, LB_FINDSTRINGEXACT, 0, (LPARAM)temp) == LB_ERR) {
						SendMessage(hListbox2, LB_ADDSTRING, NULL, LPARAM(temp));
					}	
				}
				break;
			case IDL_BUTTON_DELETE:
				isSelected = (int) SendMessage(hListbox1, LB_GETCURSEL, NULL, NULL);
				if (isSelected != -1) {
					SendMessage(hListbox1, LB_DELETESTRING, (WPARAM)isSelected, NULL);
				}

				isSelected = (int)SendMessage(hListbox2, LB_GETCURSEL, NULL, NULL);
				if (isSelected != -1) {
					SendMessage(hListbox2, LB_DELETESTRING, (WPARAM)isSelected, NULL);
				}
				break;
			case IDL_BUTTON_CLEAR:
				while ((int)SendMessage(hListbox1, LB_GETCOUNT, NULL, NULL) > 0) {
					SendMessage(hListbox1, LB_DELETESTRING, 0, NULL);
				}
				while ((int)SendMessage(hListbox2, LB_GETCOUNT, NULL, NULL) > 0) {
					SendMessage(hListbox2, LB_DELETESTRING, 0, NULL);
				}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
	{
		    hListbox1 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT, 120, 70, 200, 145, hWnd,
				(HMENU)IDL_LISTBOX1, hInst, NULL);
			hListbox2 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT, 350, 70, 200, 145, hWnd,
				(HMENU)IDL_LISTBOX2, hInst, NULL);

			hEdit = CreateWindow(TEXT("edit"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT, 600, 190, 100, 20, hWnd,
				(HMENU)IDL_EDIT1, hInst, NULL);

			CreateWindow(TEXT("BUTTON"), TEXT("Add"), WS_CHILD | WS_VISIBLE, 600, 70, 65, 20, hWnd,
				(HMENU)IDL_BUTTON_ADD, hInst, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("Clear"), WS_CHILD | WS_VISIBLE, 600, 100, 65, 20, hWnd,
				(HMENU)IDL_BUTTON_CLEAR, hInst, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("Delete"), WS_CHILD | WS_VISIBLE, 600, 130, 65, 20, hWnd,
				(HMENU)IDL_BUTTON_DELETE, hInst, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("To right"), WS_CHILD | WS_VISIBLE, 600, 160, 65, 20, hWnd,
				(HMENU)IDL_BUTTON_TORIGHT, hInst, NULL);
	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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
