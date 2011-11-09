#include "InputManager.h"
InputMannager* InputMannager::_instance=NULL;

InputMannager::InputMannager(HINSTANCE _hInstance,HWND _hWnd)
{
	this->_hInstance=_hInstance;
	this->_hWnd=_hWnd;
}
InputMannager::~InputMannager(void)
{
}
InputMannager* InputMannager::Handle(HINSTANCE _hInstance,HWND _hWnd)
{
	if (_instance==NULL)
	{
		_instance=new InputMannager(_hInstance,_hWnd);
	}
	return _instance;
}

LPDIRECTINPUTDEVICE8 InputMannager::KeyBoard()
{
	HRESULT 
		hr = DirectInput8Create
		( 
		_hInstance, 
		DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&_dinput, NULL 
		);
	if (hr!=DI_OK) return NULL;

	hr = _dinput->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL); 
	if (hr!=DI_OK) return NULL;

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);

	hr = _Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND ); 

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = _Keyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if (hr!=DI_OK) return NULL;

	hr = _Keyboard->Acquire(); 

	return _Keyboard;
}
LPDIRECTINPUTDEVICE8 InputMannager::Mouse()
{
	// Create the DirectInput object. 
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&_dinput, NULL); 

	if FAILED(hr) return FALSE; 

	// Retrieve a pointer to an IDirectInputDevice8 interface 
	hr = _dinput->CreateDevice(GUID_SysMouse, &_Mouse, NULL); 

	hr = _Mouse->SetDataFormat(&c_dfDIMouse); 

	if FAILED(hr) { 
		return NULL; 
	} 

	// Set the cooperative level 
	hr = _Mouse->SetCooperativeLevel(_hWnd, 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 

	if FAILED(hr) 
	{ 
		return NULL; 
	} 

	// Get access to the input device. 
	_Mouse->Acquire(); 	
	return _Mouse;
}