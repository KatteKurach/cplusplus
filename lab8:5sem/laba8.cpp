// laba8.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "laba8.h"
#include "TlHelp32.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#define MAX_LOADSTRING 100


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND h_listbox1;
HWND h_listbox2;

HANDLE h_mod;

int isSelected = -1;
wchar_t last_cur[500];
bool idle = false;
bool normal = false;
bool high = false;
bool real_time = false;

MODULEENTRY32 info_mod;


void view_mod(wchar_t *s, DWORD id) {
	isSelected = (int)SendMessage(h_listbox1, LB_GETCURSEL, NULL, NULL);

	if (isSelected != -1) {
		wchar_t temp[1024];
		SendMessage(h_listbox1, LB_GETTEXT, (WPARAM)isSelected, (LPARAM)temp);

		if (wcscmp(s, temp) == 0 && wcscmp(s, last_cur) != 0) {
			wcscpy(last_cur, s);
			SendMessage(h_listbox2, LB_RESETCONTENT, NULL, NULL);

			h_mod = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);
			info_mod.dwSize = sizeof(MODULEENTRY32);

			while (Module32Next(h_mod, &info_mod)) {
				SendMessage(h_listbox2, LB_ADDSTRING, NULL, LPARAM(info_mod.szModule));
			}
		}
	}
}


void view_proc() {
	PROCESSENTRY32 info_proc;
	HANDLE h_process = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	info_proc.dwSize = sizeof(PROCESSENTRY32);
	while (Process32Next(h_process, &info_proc))
	{
		wchar_t new_s[400];
		wchar_t prior[300];
		long val = info_proc.pcPriClassBase;

		swprintf_s(prior, L"%d", val);
		swprintf(new_s, L"%s    %s", info_proc.szExeFile, prior, 400);

		view_mod(new_s, info_proc.th32ProcessID);
		if ((int)SendMessage(h_listbox1, LB_FINDSTRINGEXACT, NULL, (LPARAM)new_s) == LB_ERR) {
			SendMessage(h_listbox1, LB_ADDSTRING, NULL, (LPARAM)new_s);
		}
	} 
}


DWORD get_id(wchar_t *name) {
	PROCESSENTRY32 info_proc;
	HANDLE h_process = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	info_proc.dwSize = sizeof(PROCESSENTRY32);

	while (Process32Next(h_process, &info_proc))
	{
		if (wcscmp(info_proc.szExeFile, name) == 0) {
			return info_proc.th32ProcessID;
		}
	}
}

void set_prior(HWND hWnd) {
	int isSel = -1;
	isSel = SendMessage(h_listbox1, LB_GETCURSEL, NULL, NULL);
	if (isSel != -1) {
		wchar_t temp[1024];
		wchar_t name_proc[300];

		SendMessage(h_listbox1, LB_GETTEXT, (WPARAM)isSelected, (LPARAM)temp);
		swscanf(temp, L"%s", name_proc);   //parse

		DWORD proc_id = get_id(name_proc);
		HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc_id);
		DWORD new_prior;
		if (idle) {
			new_prior = IDLE_PRIORITY_CLASS;
		}
		if (normal) {
			new_prior =NORMAL_PRIORITY_CLASS;
		}
		if (high) {
			new_prior = HIGH_PRIORITY_CLASS;
		}
		if (real_time) {
			new_prior = REALTIME_PRIORITY_CLASS;
		}
		SetPriorityClass(proc, new_prior);
		SendMessage(h_listbox1, LB_DELETESTRING, (WPARAM)isSel, NULL);
	}
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LABA8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA8));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA8));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA8);
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
			case IDM_IDLE:
			{
				idle = true;
				normal = false;
				high = false;
				real_time = false;

				set_prior(hWnd);
			}
				break;
			case IDM_NORMAL:
			{
				idle = false;
				normal = true;
				high = false;
				real_time = false;

				set_prior(hWnd);
			}
				break;
			case IDM_HIGH:
			{
				idle = false;
				normal = false;
				high = true;
				real_time = false;

				set_prior(hWnd);
			}
				break;
			case IDM_REAL_TIME: 
			{
				idle = false;
				normal = false;
				high = false;
				real_time = true;

				set_prior(hWnd);
			}
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE: {

		SetTimer(hWnd, IDC_TIMER, 100, NULL);
		h_listbox1 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT, 20, 20, 300, 400, hWnd,
			(HMENU)IDL_LISTBOX1, hInst, NULL);
		h_listbox2 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT, 330, 20, 400, 400, hWnd,
			(HMENU)IDL_LISTBOX2, hInst, NULL);
	}
		break;
	case WM_TIMER:
	{
		view_proc();
	}
		break;
	case WM_CONTEXTMENU:
	{
		HMENU hMenu = CreatePopupMenu();
		wchar_t *first_str = L"Idle";
		wchar_t *second_str = L"Normal";
		wchar_t *third_str = L"High";
		wchar_t *four_str = L"Real time";

		AppendMenu(hMenu, MFT_STRING, IDM_IDLE, (LPCWSTR)first_str);
		AppendMenu(hMenu, MFT_STRING, IDM_NORMAL, (LPCWSTR)second_str);
		AppendMenu(hMenu, MFT_STRING, IDM_HIGH, (LPCWSTR)third_str);
		AppendMenu(hMenu, MFT_STRING, IDM_REAL_TIME, (LPCWSTR)four_str);

		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
		DestroyMenu(hMenu);
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
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

