#include "EffectDieSnow.h"
#include "RSMainGame.h"

EffectDieSnow::EffectDieSnow(float x,float y)
{
	m_X = x;
	m_Y = y;
	Init();
}


EffectDieSnow::~EffectDieSnow(void)
{
}
void EffectDieSnow ::Init()
{
	m_InfoSprite.setSize(190,108);
	m_Sprite = RSMainGame::get()->getSnowManDie();
	m_iLife = true;
	m_TimeAni =0;
}
void EffectDieSnow::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.15f)
	{
		m_TimeAni -= 0.15f;			
		m_InfoSprite.NextFrame(0,6);
		if (m_InfoSprite.getCurFrame()>=5)
		{
			m_TimeAni = 0;
			m_iLife = false;
		}
	}		
}
void EffectDieSnow ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
		m_InfoSprite.setXY(m_X,m_Y);
		m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
}
void EffectDieSnow ::Release()
{

}