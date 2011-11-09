#include "Winform.h"


bool Winform::m_iSize = false;
LRESULT CALLBACK Winform::WndProc(
	HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
		return (0);		
	
	case WM_DESTROY:
		PostQuitMessage (0);
		return (0);
	case WM_SIZE:
		m_iSize = true;
		return (0);
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}

Winform::Winform(char* _AppName)
{
	szAppName = _AppName;
}


Winform::~Winform(void)
{
}
bool Winform::Register (HINSTANCE _hInstance)
{
	WNDCLASSEX   wndclassex = {0};
	wndclassex.cbSize        = sizeof(WNDCLASSEX);
	wndclassex.style         = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpfnWndProc   = WndProc;
	wndclassex.cbClsExtra    = 0;
	wndclassex.cbWndExtra    = 0;
	wndclassex.hInstance     = _hInstance;
	wndclassex.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
	wndclassex.hCursor       = LoadCursor (NULL, IDC_ARROW);
	wndclassex.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclassex.lpszMenuName  = NULL;
	wndclassex.lpszClassName = szAppName;
	wndclassex.hIconSm       = wndclassex.hIcon;

	if (!RegisterClassEx (&wndclassex))
	{
		MessageBox (NULL, TEXT ("RegisterClassEx failed!"), szAppName, MB_ICONERROR);
		return 0;
	}
	return 1;
}
bool Winform::Creater (HINSTANCE _hInstance,
	int _Width, int _Height)
{
	hwnd = CreateWindowEx (WS_EX_OVERLAPPEDWINDOW, 
		szAppName, 
		TEXT ("WindowTitle"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		_Width, 
		_Height, 
		NULL, 
		NULL, 
		_hInstance,
		NULL); 

	if (hwnd == NULL)
	{
		return 0;
	}
	ShowWindow (hwnd, 1); // Show normal
	UpdateWindow (hwnd);
	return 1;
}