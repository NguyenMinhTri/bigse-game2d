#include "EffectDiePrivate.h"
#include "RSMainGame.h"

EffectDiePrivate::EffectDiePrivate(Character* _Character ,float x, float y)
{
	m_Character = _Character ;
	m_X = x;
	m_Y = y;
	Init() ;
}


EffectDiePrivate::~EffectDiePrivate(void)
{
}
void EffectDiePrivate ::Init()
{
	m_InfoSprite.setSize(162,146);
	m_Sprite = RSMainGame::get()->getPirateDie();
	m_iLife = true;
	m_TimeAni =0;
}
void EffectDiePrivate::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.15f)
	{
		m_TimeAni -= 0.15f;			
		m_InfoSprite.NextFrame(0,8);
		if (m_InfoSprite.getCurFrame()>=7)
		{
			m_TimeAni = 0;
			m_iLife = false;
		}
	}		
}
void EffectDiePrivate ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_Character->getDirection() > 0)
	{
		m_InfoSprite.setScaleX(-1);
	}
	if(m_Character->getDirection() < 0)
	{
		m_InfoSprite.setScaleX(1);
	}
	m_InfoSprite.setXY(m_X,m_Y - 30);
	m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
}
void EffectDiePrivate ::Release()
{
}