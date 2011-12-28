#include "EffectSystem.h"
#include "RSMainGame.h"
#include "Global.h"


EffectSystem::EffectSystem(float _X, float _Y)
{
	m_X = _X;
	m_Y = _Y;
	Init();
}
EffectSystem ::EffectSystem(void)
{

}
EffectSystem::~EffectSystem(void)
{

}
void EffectSystem::Init()
{
	m_InfoSprite.setSize(170,229);
	m_Sprite = RSMainGame::get()->getEffectDie();
	m_iLife = true;
	m_TimeAni =0;
}
void EffectSystem::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.15f)
	{
		m_TimeAni -= 0.15f;			
		m_InfoSprite.NextFrame(0,8);
		if (m_InfoSprite.getCurFrame()== 7)
		{
			m_iLife = false;
			m_TimeAni = 0;
		}
	}		
}
void EffectSystem::Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		m_InfoSprite.setXY(-43.5+m_X,-60+m_Y);
		m_Sprite->Draw(_MWorld,m_InfoSprite,_Handler);
	}
}
void EffectSystem::Release () 
{

}
void EffectSystem ::Animation(float _Time)
{

}
void EffectSystem ::UpdateStatus(float _Time)
{

}
