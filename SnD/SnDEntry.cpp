#include <Windows.h>
#include "SnDLog.h"

using namespace  log_exceptions;
#define          WIN32_LEAN_AND_MEAN

LPCWSTR lpcwsClassName, lpcwstWindowName;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void             registerWindow(HINSTANCE);
LPARAM           messageLoop();

int WINAPI       WinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPSTR lpCmdLine, int nCmdShow) {

	UNREFERENCED_PARAMETER(pInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	lpcwsClassName   = L"SND_Win32";
	lpcwstWindowName = L"Swords N Damsels";

	HWND hdlWindow = {};
	try {
		registerWindow(hInstance);
		hdlWindow  = CreateWindowEx(0,
			lpcwsClassName,
			lpcwstWindowName,
			WS_OVERLAPPEDWINDOW, 0, 0,
			800, 600,
			nullptr, nullptr, hInstance,
			nullptr);
		ShowWindow(hdlWindow, nCmdShow);
		if (!hdlWindow) throw;
	}
	catch (SnDLog &snd) {
		//snd.writeExceptionToFile();
	}

	return (int) messageLoop();
}

void registerWindow(HINSTANCE hInstance) {
	WNDCLASSEX wnd = {};
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.lpszClassName = lpcwsClassName;

	if (!RegisterClassEx(&wnd)) throw;
}

LPARAM messageLoop() {
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_QUIT:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
