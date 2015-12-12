#include <windows.h>
#include <objidl.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <tchar.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

WORD x, y;
HBRUSH hBrush;
bool heart_is_activated = false;
bool tree_is_activated = false;
bool ball_is_activatad = false;
bool snowflake = false;
TCHAR out1[] = _T("Alexey,Happy New Year!)");

class pict {
public:
	std::string type;
	int x, y;

	pict() {}
	pict(std::string s, int x, int y) : type(s), x(x), y(y) {}
};

std::vector<pict> points;


VOID OnPaint(HDC hdc)
{
	POINT Pt[10];
	Pt[0].x = x;
	Pt[0].y = y;
	Pt[1].x = x + 20;
	Pt[1].y = y;
	Pt[2].x = x + 30;
	Pt[2].y = y + 10;
	Pt[3].x = x + 40;
	Pt[3].y = y;
	Pt[4].x = x + 60;
	Pt[4].y = y;
	Pt[5].x = x + 70;
	Pt[5].y = y + 10;
	Pt[6].x = x + 70;
	Pt[6].y = y + 30;
	Pt[7].x = x + 30;
	Pt[7].y = y + 70;
	Pt[8].x = x - 10;
	Pt[8].y = y + 30;
	Pt[9].x = x - 10;
	Pt[9].y = y + 10;

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, hBrush);
	SelectObject(hdc, pen);
	Polygon(hdc, Pt, 10);
	DeleteObject(hBrush);
	DeleteObject(pen);
}


VOID OnPaint1(HDC hdc)
{
	POINT Pt[23];
	Pt[0].x = x;
	Pt[0].y = y;
	Pt[1].x = x + 20;
	Pt[1].y = y + 20;
	Pt[2].x = x + 10;
	Pt[2].y = y + 20;
	Pt[3].x = x + 30;
	Pt[3].y = y + 40;
	Pt[4].x = x + 20;
	Pt[4].y = y + 40;
	Pt[5].x = x + 40;
	Pt[5].y = y + 60;
	Pt[6].x = x + 30;
	Pt[6].y = y + 60;
	Pt[7].x = x + 50;
	Pt[7].y = y + 80;
	Pt[8].x = x + 40;
	Pt[8].y = y + 80;
	Pt[9].x = x + 60;
	Pt[9].y = y + 100;
	Pt[10].x = x + 50;
	Pt[10].y = y + 100;
	Pt[11].x = x + 70;
	Pt[11].y = y + 120;
	Pt[12].x = x - 70;
	Pt[12].y = y + 120;
	Pt[13].x = x - 50;
	Pt[13].y = y + 100;
	Pt[14].x = x - 60;
	Pt[14].y = y + 100;
	Pt[15].x = x - 40;
	Pt[15].y = y + 80;
	Pt[16].x = x - 50;
	Pt[16].y = y + 80;
	Pt[17].x = x - 30;
	Pt[17].y = y + 60;
	Pt[18].x = x - 40;
	Pt[18].y = y + 60;
	Pt[19].x = x - 20;
	Pt[19].y = y + 40; 
	Pt[20].x = x - 30;
	Pt[20].y = y + 40;
	Pt[21].x = x - 10;
	Pt[21].y = y + 20;
	Pt[22].x = x - 20;
	Pt[22].y = y + 20;

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 100, 200));
	SelectObject(hdc, hBrush);
	SelectObject(hdc, pen);
	Polygon(hdc, Pt, 23);
	DeleteObject(hBrush);
	DeleteObject(pen);
}

VOID OnPaint3(HDC hdc){
	int r = rand()%256;
	int g = rand() % 256;
	int b = rand() % 256;
	HBRUSH brushColor = CreateSolidBrush(RGB(r, g, b));
	SelectObject(hdc, brushColor);
	int width = 10;
	int height = 10;
	// Draw the ellipse.
	Ellipse(hdc, x, y, x + width, y + height);

	DeleteObject(brushColor);

}
VOID text_draw(HDC hdc){
	Graphics graphic(hdc);
	SolidBrush brush(Color(255, 0, 0));
	FontFamily fontfamily(L"Times New Roman");
	Font font(&fontfamily, 20, FontStyleItalic, UnitPixel);
	PointF point(10.0f, 20.0f);

	graphic.DrawString(L"Alexey,Happy New Year!)", -1, &font, point, &brush);
}
void drawKoch(HDC hdc, int xa, int ya, int xe, int ye, int i) {
	if (i == 0) {
		HPEN c;
		c = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
		SelectObject(hdc, hBrush);
		SelectObject(hdc, c);
		MoveToEx(hdc, xa, ya, NULL);
		LineTo(hdc, xe, ye);
		DeleteObject(hBrush);
		DeleteObject(c);
	}
	else {
		int xb = xa + (xe - xa) * 1 / 3;
		int yb = ya + (ye - ya) * 1 / 3;

		int xd = xa + (xe - xa) * 2 / 3;
		int yd = ya + (ye - ya) * 2 / 3;

		double cos60 = 0.5;
		double sin60 = -0.866;
		double xcc = xb + (xd - xb) * cos60 - sin60 * (yd - yb);
		double ycc = yb + (xd - xb) * sin60 + cos60 * (yd - yb);
		int xc = (int)xcc;
		int yc = (int)ycc;

		drawKoch(hdc, xa, ya, xb, yb, i - 1);
		drawKoch(hdc, xb, yb, xc, yc, i - 1);
		drawKoch(hdc, xc, yc, xd, yd, i - 1);
		drawKoch(hdc, xd, yd, xe, ye, i - 1);
	}
}

void drawTriangleKoch(HDC hdc, int xa, int ya, int xe, int ye, int i) {
	int xs = xa;
	int ys = ya;
	int a = abs(xa - xe);
	double si = 0.866;
	double co = 0.5;
	int nx = (int)(1.0 * (xs + a) - 1.0 * a * co);;
	int ny = (int)(1.0 * ys + 1.0 * a * si);
	drawKoch(hdc, xs, ys, xs + a, ys, i);
	drawKoch(hdc, xs + a, ys, nx, ny, i);
	drawKoch(hdc, nx, ny, xs, ys, i);
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd; 
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_CREATE:
		CreateWindow(_T("BUTTON"), _T("clear !"), WS_CHILD | WS_VISIBLE, 10, 0, 45, 20, hWnd, (HMENU)1, NULL, NULL);
		CreateWindow(_T("BUTTON"), _T("Heart"), WS_CHILD | WS_VISIBLE, 55, 0, 45, 20, hWnd, (HMENU)2, NULL, NULL);
		CreateWindow(_T("BUTTON"), _T("Tree"), WS_CHILD | WS_VISIBLE, 100, 0, 45, 20, hWnd, (HMENU)3, NULL, NULL);
		CreateWindow(_T("BUTTON"), _T("Balls"), WS_CHILD | WS_VISIBLE, 145, 0, 45, 20, hWnd, (HMENU)4, NULL, NULL);
		CreateWindow(_T("BUTTON"), _T("Snowflake"), WS_CHILD | WS_VISIBLE, 190, 0, 75, 20, hWnd, (HMENU)5, NULL, NULL);
	break;
	case WM_COMMAND:
		switch (wParam)
		{
			case 1:
				RECT work_area;
				work_area = { 0, 0, 1300, 1300 };
				InvalidateRect(hWnd, &work_area, true);
				UpdateWindow(hWnd);
				ball_is_activatad = false;
				tree_is_activated = false;
				heart_is_activated = false;
				snowflake = false;
			break;
			case 2:
				ball_is_activatad = false;
				tree_is_activated = false;
				snowflake = false;
				heart_is_activated = true;
			break;
			case 3:
				ball_is_activatad = false;
				heart_is_activated = false;
				snowflake = false;
				tree_is_activated =  true;
				break;
			case 4:
				heart_is_activated = false;
				tree_is_activated = false;
				snowflake = false;
				ball_is_activatad = true;
				break;
			case 5:
				heart_is_activated = false;
				tree_is_activated = false;
				ball_is_activatad = false;
				snowflake = true;
				break;
			}
		break;
	case WM_LBUTTONDOWN:
	{
		WORD xPos, yPos, nSize;
		TCHAR szBuf[80];
		hdc = GetDC(hWnd);
		// Сохраняем координаты курсора мыши
		 x = LOWORD(lParam);
		 y = HIWORD(lParam);
         nSize = wsprintf(szBuf, TEXT("(%d, %d)"), x, y);

		 if (heart_is_activated) {
			 pict picture("heart", x, y);
			 points.push_back(picture);
			 OnPaint(hdc); 
		 }

		 if (tree_is_activated){
			 pict picture("tree", x, y);
			 points.push_back(picture);
			 OnPaint1(hdc);
			 text_draw(hdc);
			 
		 }

		 if (ball_is_activatad){
			 pict picture("ball", x, y);
			 points.push_back(picture);
			 OnPaint3(hdc);
		 }

		 if (snowflake){
			 pict picture("snowflake", x, y);
			 points.push_back(picture);
			 drawTriangleKoch(hdc, x - 50, y - 25, x + 50, y + 25, 4);
		 }
		 ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
	/*	for (int i = 0; i < (int)points.size(); i++) {
			int x = points[i].x;
			int y = points[i].y;
			if (points[i].type == "heart") {
				OnPaint(hdc);
			}
			else if (points[i].type == "tree") {
				OnPaint1(hdc);
				text_draw(hdc);
			}
			else if (points[i].type == "ball") {
				OnPaint3(hdc);
			}
			else if (points[i].type == "snowflake") {
			
				drawTriangleKoch(hdc, x - 50, y - 25, x + 50, y + 25, 4);
			}
		}*/
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc
