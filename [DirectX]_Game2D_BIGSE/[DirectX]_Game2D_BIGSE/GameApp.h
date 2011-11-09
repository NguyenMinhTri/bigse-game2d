#pragma once
#include "DXDevice.h"
#include "Winform.h"
#include "Global.h"
#include "GamePlay.h"
#include <dinput.h>
class GameApp
{


public:
	GameApp(void);
	~GameApp(void);
	void Input ();
	bool Init ( HINSTANCE _hInstance,char* _Name);
	
	void Run ();
private:
	/************************************************************************/
	/* Member private                                                                     */
	/************************************************************************/
	DXDevice* m_Device;
	Winform* m_form ;
	int m_TotalFPS;
	int m_LastTime, m_NowTime, m_SaveTime;
	int m_DetaTime;

	GamePlay* m_GamePlay; 
	LPDIRECTINPUTDEVICE8 m_Keyboard;
	LPDIRECTINPUTDEVICE8 m_Mouse;

	/************************************************************************/
	/* Function private                                                                     */
	/************************************************************************/
	
	/* Process mouse */
	void ProcessMouse ();

	/* process keyboard */
	void ProcessKeyBoard();

	/* Game update */
	void Update (float _DetaTime);

	/* Draw */
	void Draw () ;

	/* release all data */
	void Release ();
};

