#include <Windows.h>
#include "log_exceptions\SnDLog.h"

using namespace  log_exceptions;
#define          WIN32_LEAN_AND_MEAN

SnDLog           sndLog;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI       WinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPSTR lpCmdLine, int nCmdShow) {

	UNREFERENCED_PARAMETER(pInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HWND hdlWindow      = {};
	WNDCLASSEX wndClass = {};

}