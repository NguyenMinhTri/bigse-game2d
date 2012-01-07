#include "GameApp.h"

#include <Strsafe.h>
#include <dinput.h>
#include "InputManager.h"
#include <intsafe.h>
#include "iState.h"
#include "DXManager.h"
#include <time.h>
GameApp::GameApp(void)
{
	m_TotalFPS = 0;
	m_LastTime = m_NowTime = timeGetTime();
	m_SaveTime =0;

}


GameApp::~GameApp(void)
{
}

bool GameApp::Init(HINSTANCE _hInstance,char* _Name)
{
	 srand ( time(NULL) );
	m_form = new Winform(_Name);
	if (!m_form->Register(_hInstance))
		return false;

	if (!m_form->Creater(_hInstance,g_SCREEN_WIDTH,g_SCREEN_HEIGHT))
		return false;

	m_Device = new DXDevice();

	if (!m_Device->Create_DirectX()) return false;

	if(!m_Device->Create_Para(false,m_form->getHWND())) return false;

	if (!m_Device->Create_Device(m_form->getHWND())) return false;

	m_Device->CreateBuffer();
	DXManager::Instance()->setDevice(m_Device->getDevice());
	m_Keyboard=InputMannager::Handle(_hInstance,m_form->getHWND())->KeyBoard();
	m_Mouse =InputMannager::Handle(_hInstance,m_form->getHWND())->Mouse();
	if (m_Keyboard==NULL|| m_Mouse==NULL)
	{
		return false;
	}

	m_GamePlay = new GamePlay(m_Device->getDevice());
	m_GamePlay->Init();
	return true;
}
void GameApp::Run()
{
	MSG m_msg;
	bool done = false;
	while(!done)
	{
		if (PeekMessage(&m_msg,NULL,0,0,PM_REMOVE))
		{
			if(m_msg.message==WM_QUIT) 
			{
				done=true;
			}
			TranslateMessage (&m_msg);
			DispatchMessage (&m_msg);
		} 	

		//////////////////////////////////////////////////////////////////////////		
		// Update

		//////////////////////////////////////////////////////////////////////////
		// Render
		m_NowTime = timeGetTime();		
		m_DetaTime = m_NowTime - m_LastTime;

		if (m_DetaTime > 1000.0f/600.0f)
		{			
			m_LastTime = m_NowTime;
			m_SaveTime+= m_DetaTime;
			m_TotalFPS++;
			Input();
			Update(m_DetaTime/1000.0f);
			Draw();

			if(m_SaveTime >= 1000)
			{	

				float FPS = (float)m_TotalFPS*1000.0f / (float)m_SaveTime;
				char c[100];
				sprintf(c,"Game FPS: %f",FPS);
				SetWindowText(m_form->getHWND(), c );
				m_TotalFPS = 0;
				m_SaveTime -=1000;
			}
		} 
	}
}
void GameApp::Input  ()
{
	ProcessKeyBoard();
	ProcessMouse();
}
void GameApp::Update(float _Time)
{
	m_GamePlay->Update(_Time);

}
void GameApp::Draw()
{
	m_GamePlay->Draw();

}

void GameApp::ProcessKeyBoard()
{
	DIDEVICEOBJECTDATA _KeyEvents[ KEYBOARD_BUFFER_SIZE ];
	BYTE  _KeyStates[256];

	// Collect all key states first
	if(m_Keyboard->GetDeviceState( sizeof(_KeyStates), _KeyStates))
	{
		m_Keyboard->Acquire();

	}else{
		// Collect all buffered events
		DWORD dwElements = KEYBOARD_BUFFER_SIZE;
		HRESULT hr = m_Keyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0 );

		// Scan through all data, check if the key is pressed or released
		for (int i=0;i<256;i++)
		{
			if ((_KeyStates[i] & 0x80) > 0)
			{
				//Is Key down
				m_GamePlay->GetCurState()->IsKeyDown(i);
			}
		}
		for( DWORD i = 0; i < dwElements; i++ ) 
		{
			int KeyCode = _KeyEvents[i].dwOfs;
			int KeyState = _KeyEvents[i].dwData;
			// 		if ((_KeyStates[(int)i] & 0x80) > 0)
			// 		{
			// 			//Is Key down
			// 			_GamePlay->GetCurState()->IsKeyDown(KeyCode);
			// 		}
			if ( (KeyState & 0x80) > 0)
			{
				// On key down
				m_GamePlay->GetCurState()->OnKeyDown(KeyCode);
			}
			else 
			{
				// On key Up
				m_GamePlay->GetCurState()->OnKeyUp(KeyCode);
			}
		}
	}
}
void GameApp::ProcessMouse()
{
	POINT Postion;
	DIMOUSESTATE mouseState;
	m_Mouse->Poll();
	if (!SUCCEEDED(m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE),&mouseState)))
	{
		//mouse device lose, try to re-acquire
		m_Mouse->Acquire();
	}
	else
	{
		GetCursorPos(&Postion);
		ScreenToClient(m_form->getHWND(), &Postion);
		m_GamePlay->GetCurState()->ProcessMouse(mouseState,Postion);
	}
	//get mouse position on screen
	
}