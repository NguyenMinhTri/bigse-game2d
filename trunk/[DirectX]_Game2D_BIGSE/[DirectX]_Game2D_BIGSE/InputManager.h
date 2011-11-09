#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#define KEYBOARD_BUFFER_SIZE	1024
#define DIRECTINPUT_VERSION 0x0800
class InputMannager
{
private:
	LPDIRECTINPUT8       _dinput;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;
	LPDIRECTINPUTDEVICE8  _Mouse;
	HINSTANCE _hInstance;
	HWND _hWnd;
	static InputMannager* _instance;
	InputMannager(HINSTANCE _hInstance,HWND _hWnd);
public:	
	~InputMannager(void);
	LPDIRECTINPUTDEVICE8 KeyBoard();
	LPDIRECTINPUTDEVICE8 Mouse();
	static InputMannager* Handle(HINSTANCE _hInstance,HWND _hWnd);
};

