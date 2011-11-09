#pragma once
#include <Windows.h>
class Winform
{
private:
	HWND hwnd;
	char* szAppName;

public:
	static bool m_iSize;
	Winform(char* _AppName);
	~Winform(void);
	static LRESULT CALLBACK WndProc (HWND hwnd, UINT message,
		WPARAM wParam, LPARAM lParam);
	bool Register (HINSTANCE _hInstance);
	bool Creater (HINSTANCE _hInstance,int _Width, int _Height);
	HWND getHWND ()
	{
		return hwnd;
	}

};


