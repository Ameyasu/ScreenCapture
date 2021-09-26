// ScreenCapture.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ScreenCapture.h"
#include "Capture.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
	LoadStringW(hInstance, IDC_SCREENCAPTURE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SCREENCAPTURE));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SCREENCAPTURE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SCREENCAPTURE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Capture* s_cap = nullptr;

	static bool s_mouseDrag = false;
	static int s_mouseXPrev = 0;
	static int s_mouseYPrev = 0;

	static TCHAR s_colorText[64] = {};
	static int s_colorTextLen = 0;
	static int s_colorTextX = 0;
	static int s_colorTextY = 0;

	switch (message)
	{
	case WM_CREATE:
	{
		RECT r;
		GetClientRect(hWnd, &r);

		s_cap = new Capture;
		s_cap->createCapBuf(r.right - r.left, r.bottom - r.top);
		s_cap->setCapX(0);
		s_cap->setCapY(0);

		SetTimer(hWnd, 100, 1000 / 30, nullptr);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		s_mouseDrag = true;
		s_mouseXPrev = LOWORD(lParam);
		s_mouseYPrev = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		s_mouseDrag = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		if (s_mouseDrag)
		{
			int moveX = mouseX - s_mouseXPrev;
			int moveY = mouseY - s_mouseYPrev;

			s_cap->setCapX(s_cap->getCapX() - moveX);
			s_cap->setCapY(s_cap->getCapY() - moveY);

			s_mouseXPrev = mouseX;
			s_mouseYPrev = mouseY;
		}

		s_colorTextX = mouseX;
		s_colorTextY = mouseY;

		RGB24 color = s_cap->getColor(s_colorTextX, s_colorTextY);
		s_colorTextLen = _stprintf_s(s_colorText, TEXT("(R,G,B)=(%d,%d,%d)"), color.r, color.g, color.b);
	}
	break;
	case WM_SIZE:
	{
		switch (wParam)
		{
		case SIZE_RESTORED:
		case SIZE_MAXIMIZED:
		{
			UINT xSize = LOWORD(lParam);
			UINT ySize = HIWORD(lParam);
			s_cap->createCapBuf(xSize, ySize);
		}
		break;
		case SIZE_MINIMIZED:
		{
			s_cap->destroyCapBuf();
		}
		break;
		}
	}
	break;
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		s_cap->paintCap(hdc, 0, 0);
		TextOut(hdc, s_colorTextX, s_colorTextY - 16, s_colorText, s_colorTextLen);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
	{
		s_cap->capDesk();
		InvalidateRect(hWnd, nullptr, FALSE);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 100);

		delete s_cap;
		s_cap = nullptr;

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
