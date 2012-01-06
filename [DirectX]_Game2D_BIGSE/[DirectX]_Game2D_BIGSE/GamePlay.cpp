#pragma once
#include "GamePlay.h"
#include "State_Play.h"
#include "StateWorldMap.h"

GamePlay::GamePlay(LPDIRECT3DDEVICE9 Device):iPlay(Device)
{
	m_CurState = new StateWorldMap(this);
	m_NextState = m_CurState;
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
	
}
void GamePlay::Release()
{
	m_CurState->Release();
	m_NextState->Release();
};
