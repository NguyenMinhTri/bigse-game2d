#include "GamePlay.h"
#include "State_Play.h"

GamePlay::GamePlay(LPDIRECT3DDEVICE9 Device):iPlay(Device)
{
	m_CurState = new State_Play(this);
	m_NextState = new State_Play (this);
}
GamePlay::~GamePlay(void)
{
}
void GamePlay::Init()
{
	m_CurState->Init();
}
void GamePlay::Update(float _Time)
{
	if(m_CurState->GetIDState()!=m_NextState->GetIDState())
	{
		m_CurState->Release();
		m_CurState=m_NextState;
		m_CurState->Init();
	}
	else
	{
		m_CurState->Update(_Time);
	}
}
void GamePlay::Draw()
{
	m_CurState->Draw();
	/*m_Device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,0,255),1.0f,0);
	if(m_Device->BeginScene())
	{
		/ *_Device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(1,0,0),1.0f,0);* /
		Sprite_Handler->Begin(D3DXSPRITE_ALPHABLEND);
		m_CurState->Render(Sprite_Handler);
		Sprite_Handler->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);*/
}
void GamePlay::Release()
{
	m_CurState->Release();
	m_NextState->Release();
};
