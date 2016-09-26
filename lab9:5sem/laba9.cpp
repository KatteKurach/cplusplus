
#include "stdafx.h"
#include "laba9.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND h_listbox1;
HWND h_edit1;
HWND h_edit2;
HWND h_edit3;

WCHAR path[1024];
WCHAR new_val[1024];
WCHAR s_main_key[100];
HKEY main_key = HKEY_CURRENT_USER;

int isSelected = -1;

DWORD str_to_dword(wchar_t *str) {
	DWORD x = 0;
	int i = 0;
	bool neg = false;
	if (str[0] == '-') {
		i++;
		neg = true;
	}
	int len = wcslen(str);
	for (i; i < len; i++) {
		x *= 10;
		x += str[i] - '0';
	}
	return x * (neg ? -1 : 1);
}
void get_key(HWND hWnd) {
	GetWindowText(h_edit1, s_main_key, 100);
	if (wcscmp(s_main_key,L"HKEY_CLASSES_ROOT") == 0) {
		main_key = HKEY_CLASSES_ROOT;
	}
	if (wcscmp(s_main_key, L"HKEY_CURRENT_CONFIG") == 0) {
		main_key = HKEY_CURRENT_CONFIG;
	}
	if (wcscmp(s_main_key, L"HKEY_CURRENT_USER") == 0) {
		main_key = HKEY_CURRENT_USER;
	}
	if (wcscmp(s_main_key, L"HKEY_LOCAL_MACHINE") == 0) {
		main_key = HKEY_LOCAL_MACHINE;
	}
	if (wcscmp(s_main_key, L"HKEY_USERS") == 0) {
		main_key = HKEY_USERS;
	}
}

void get_data(HWND hWnd) {
	SendMessage(h_listbox1, LB_RESETCONTENT, NULL, NULL);
	HKEY k;
	if (RegOpenKeyEx(main_key, path, 0, KEY_READ, &k) != ERROR_SUCCESS) {
		MessageBox(hWnd, L"Write the correct path!", L"Error", MB_OK);
	}
	for (int i = 0; ; i++) {
		TCHAR file[4024]; //name
		BYTE data[4024];
		DWORD cFile = 4024;
		DWORD cData = 4024;
		DWORD type;
		void* lpdata = malloc(cData);
		if (RegEnumValue(k, i, file, &cFile, NULL, &type, (LPBYTE)data, &cData) == ERROR_SUCCESS) {
			TCHAR out[500];
			if (wcscmp(file, L"") == 0) {
				wcscpy(file, L"default");
			}
			if (type == REG_BINARY) {
				TCHAR temp[100];
				for (int i = 0; i < cData; i++) {
					for (int j = 0; j < 8; j++) {
						if ((data[i] >> j) & 1) {
							temp[i * 8 + 7 - j] = '1';
						}
						else {
							temp[i * 8 + 7 -j] = '0';
						}
					}
				}
				temp[cData * 8] = '\0';
				swprintf(out, L"%s  %s   REG_BINARY", file, temp, 500);
				SendMessage(h_listbox1, LB_ADDSTRING, NULL, (LPARAM)out);
			}
			if (type == REG_DWORD) {
				swprintf(out, L"%s  %ld   REG_DWORD", file, *((DWORD*)data), 500);
				SendMessage(h_listbox1, LB_ADDSTRING, NULL, (LPARAM)out);
			}
			if (type == REG_SZ) {
				if (wcscmp((WCHAR*)data, L"") == 0) {
					wcscpy((WCHAR*)data, L"null");
				}
				swprintf(out, L"%s  %s    REG_SZ", file, (LPWSTR)data, 500);
				SendMessage(h_listbox1, LB_ADDSTRING, NULL, (LPARAM)out);
			}
			if (type == REG_EXPAND_SZ) {
				swprintf(out, L"%s  %s    REG_EXPAND_SZ", file, (LPWSTR)data, 500);
				SendMessage(h_listbox1, LB_ADDSTRING, NULL, (LPARAM)out);
			}
		}
		else {
			break;
		}
	}
}

void change_val(HWND hWnd) {
	isSelected = (int)SendMessage(h_listbox1, LB_GETCURSEL, NULL, NULL);

	if (isSelected != -1) {
		wchar_t temp[1024];
		SendMessage(h_listbox1, LB_GETTEXT, (WPARAM)isSelected, (LPARAM)temp);
		wchar_t name[100];
		wchar_t val[100];
		wchar_t type[100];
		swscanf(temp, L"%s  %s    %s", name, val, type);
		if (wcscmp(new_val, L"") != 0) {
			HKEY key;
			if (RegOpenKeyEx(main_key, path, 0, KEY_WRITE, &key) != ERROR_SUCCESS) {
				MessageBox(hWnd, path, L"ok", MB_OK);
			}
			DWORD tp = REG_SZ;
			if (wcscmp(type, L"REG_SZ") == 0) { 
				tp = REG_SZ; 
				RegSetValueEx(key, name, 0, tp, (BYTE*)new_val, sizeof(wchar_t) * (wcslen(new_val) + 1));
			}
			if (wcscmp(type, L"REG_DWORD") == 0) { 
				tp = REG_DWORD; 
				DWORD temp = str_to_dword(new_val);
				RegSetValueEx(key, name, 0, tp, (BYTE*)&temp, sizeof(DWORD));
			}
			if (wcscmp(type, L"REG_EXPAND_SZ") == 0) { 
				tp = REG_EXPAND_SZ; 
				RegSetValueEx(key, name, 0, tp, (BYTE*)new_val, sizeof(wchar_t) * (wcslen(new_val) + 1));
			}
			if (wcscmp(type, L"REG_BINARY") == 0) { 
				tp = REG_BINARY;  
			}
		}
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
    LoadStringW(hInstance, IDC_LABA9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA9));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA9));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA9);
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
			case IDL_BUTTON_SEARCH:
			{
				GetWindowText(h_edit2, path, 1024);
				get_key(hWnd);
				get_data(hWnd);
			}
			break;
			case IDL_BUTTON_CHANGE:
			{
				GetWindowText(h_edit3, new_val, 1024);
				change_val(hWnd);
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
	case WM_CREATE:
	{
		h_edit1 = CreateWindow(TEXT("edit"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL, 20, 20, 300, 30, hWnd,
			(HMENU)IDL_EDIT1, hInst, NULL);
		h_edit2 = CreateWindow(TEXT("edit"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL , 20, 60, 300, 30, hWnd,
			(HMENU)IDL_EDIT2, hInst, NULL);
		h_edit3 = CreateWindow(TEXT("edit"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT, 20, 420, 300, 30, hWnd,
			(HMENU)IDL_EDIT3, hInst, NULL);
		h_listbox1 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_SORT, 20, 100, 800, 300, hWnd,
			(HMENU)IDL_LISTBOX1, hInst, NULL);

		CreateWindow(TEXT("BUTTON"), TEXT("Search"), WS_CHILD | WS_VISIBLE, 340, 60, 70, 30, hWnd,
			(HMENU)IDL_BUTTON_SEARCH, hInst, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("Change"), WS_CHILD | WS_VISIBLE, 330, 420, 70, 30, hWnd,
			(HMENU)IDL_BUTTON_CHANGE, hInst, NULL);
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

