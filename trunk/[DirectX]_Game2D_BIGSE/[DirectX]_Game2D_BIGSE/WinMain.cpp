#include <windows.h>
#include "Winform.h"
#include "DXDevice.h"
#include "GameApp.h"


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	GameApp* m_Game;
	m_Game = new GameApp();

	m_Game->Init(hInstance,"FPS");

	m_Game->Run();

	return 1;
}
