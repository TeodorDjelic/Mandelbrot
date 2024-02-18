#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR pCmdLine, int nCmdShow)
{
	srand(GetTickCount64());

	const wchar_t CLASS_NAME[] = L"МОЈА КЛАСА";
	
	WNDCLASS myClass = {};

	myClass.style = CS_DBLCLKS;
	myClass.lpfnWndProc = WindowProc;
	myClass.hInstance = hInstance;
	myClass.lpszClassName = CLASS_NAME;

	RegisterClass(&myClass);

	HWND hwnd = CreateWindowEx(
		WS_EX_CONTEXTHELP | WS_EX_TRANSPARENT,
		CLASS_NAME,
		L"ПОЗДРАВ",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == 0) {
		printf("Could not create a window.");
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, hwnd, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch (uMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			int izbor = rand();

			int clr;

			switch (izbor % 3)
			{
				case 0: {
					clr = COLOR_HOTLIGHT;
					break;
				}
				case 1: {
					clr = COLOR_3DSHADOW;
					break;
				}
				case 2: {
					clr = COLOR_ACTIVECAPTION;
					break;
				}
			}

			HBRUSH brush = CreateHatchBrush(HS_DIAGCROSS,
				GetSysColor(clr));

			printf("EE");

			FillRect(hdc, &ps.rcPaint, brush);

			EndPaint(hwnd, &ps);

			return 0;
		}
		case WM_CLOSE:
		{
			if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL)
				== IDOK)
			{
				DestroyWindow(hwnd);
			}

			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	} 
	
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}