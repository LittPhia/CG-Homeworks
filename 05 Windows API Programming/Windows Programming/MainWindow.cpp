// INCLUDES ///////////////////////////////////////////////

#include <windows.h> // include all the windows headers
#include <windowsx.h> // include useful macros
#include <iostream>
#include <cmath>

// DEFINES ////////////////////////////////////////////////

#define WINDOW_CLASS_NAME "WINCLASS"

#define VK_C	0x41 + 'c' - 'a'
#define VK_R	0x41 + 'r' - 'a'
#define DEFAULTBKCOLOR RGB(0, 0, 0)
#define GREENBKCOLOR RGB(0, 255, 0)
#define BLUEBKCOLOR RGB(0, 0, 255)

#define KEY_DOWN(vkey) (GetAsyncKeyState(vkey) & 0x8000 ? 1 : 0)
#define KEY_UP(vkey) (GetAsyncKeyState(vkey) & 0x8000 ? 0 : 1)

// PROTOYTPES /////////////////////////////////////////////

BOOL SetBackgroundColor(HWND hwnd, COLORREF color);
BOOL SendRepaintBkMessage(HWND hwnd);
BOOL DrawRectangle(HDC hdc, int center_X, int center_Y, int width, int height);
BOOL DrawCircle(HDC hdc, int center_X, int center_Y, int radius);

// FUNCTIONS //////////////////////////////////////////////

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {

		case WM_KEYDOWN: {
			HDC gdc = GetDC(hwnd);
			RECT rect;
			GetClientRect(hwnd, &rect);
			SetBkMode(gdc, TRANSPARENT);
			SetTextColor(gdc, RGB(255, 255, 255));

			switch (wparam) {

				case VK_C: {
					DrawCircle(gdc,
						rect.right / 2,
						rect.bottom / 2,
						7 * rect.right / 20);			// 35% of user window's width
					TextOut(gdc,
						rect.right / 2 - 14,
						rect.bottom / 2 + 35 * rect.right / 100,
						"Circle", strlen("Circle"));
				} break;

				case VK_R: {
					DrawRectangle(gdc,
						rect.right / 2,
						rect.bottom / 2,
						3 * rect.right / 5,			// 60% of user window's width
						2 * rect.bottom / 5);		// 40% of user window's height
					TextOut(gdc,
						rect.right / 2 - 22,
						rect.bottom / 2 + 1 * rect.bottom / 5,
						"Rectangle", strlen("Rectangle"));
				} break;

				case VK_ESCAPE: {
					SendMessage(hwnd, WM_DESTROY, NULL, NULL);
				} break;

				default: break;
			}
			ReleaseDC(hwnd, gdc);

		} break;

		case WM_KEYUP: {
			SendRepaintBkMessage(hwnd);
		} break;

		case WM_LBUTTONDOWN: {
			SetBackgroundColor(hwnd, GREENBKCOLOR);
			SendRepaintBkMessage(hwnd);
		} break;

		case WM_RBUTTONDOWN: {
			SetBackgroundColor(hwnd, BLUEBKCOLOR);
			SendRepaintBkMessage(hwnd);
		} break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP: {
			SetBackgroundColor(hwnd, DEFAULTBKCOLOR);
			SendRepaintBkMessage(hwnd);
		} break;

		default: break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

// WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow) {
	WNDCLASSEX winclass;
	HWND hwnd;
	MSG msg;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC |
		CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
		return 0;

	if (!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME, "Your Basic Window",
		WS_POPUP | WS_VISIBLE,
		0, 0, 800, 800, NULL, NULL, hinstance, NULL)))
		return 0;
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


///////////////////////////////////////////////////////////

BOOL SetBackgroundColor(HWND hwnd, COLORREF color) {
	return DeleteObject((HBRUSH)SetClassLong(hwnd,
		GCL_HBRBACKGROUND,
		(LONG)CreateSolidBrush(color)));
}

BOOL SendRepaintBkMessage(HWND hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);
	InvalidateRect(hwnd, &rect, TRUE);
	return PostMessage(hwnd, WM_PAINT, NULL, NULL);
}

BOOL DrawRectangle(HDC hdc, int center_X, int center_Y, int width, int height) {
	return Rectangle(hdc,
		center_X - width / 2,
		center_Y - height / 2,
		center_X + width / 2,
		center_Y + height / 2);
}

BOOL DrawCircle(HDC hdc, int center_X, int center_Y, int radius) {
	return Ellipse(hdc,
		center_X - radius,
		center_Y - radius,
		center_X + radius,
		center_Y + radius);
}
