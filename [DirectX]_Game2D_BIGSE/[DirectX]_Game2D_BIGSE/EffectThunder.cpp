#include "EffectThunder.h"
#include "RSMainGame.h"

EffectThunder::EffectThunder(float x, float y)
{
	m_X = x;
	m_Y = y;
	Init();
}

EffectThunder::~EffectThunder(void)
{
}

void EffectThunder::Init()
{
	m_InfoSprite.setSize(182,129);
	m_Sprite = RSMainGame::get()->getEffectThunder();
	m_iLife = true;
	m_TimeAni =0;
}

void EffectThunder ::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.15f)
	{
		m_TimeAni -= 0.15f;			
		m_InfoSprite.NextFrame(0,4);
		if (m_InfoSprite.getCurFrame()>=3)
		{
			m_TimeAni = 0;
			m_iLife = false;
		}
	}		
}

void EffectThunder ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		m_InfoSprite.setScaleXY(2.0f,2.0f);
		m_InfoSprite.setXY(m_X - 50,m_Y);
		m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
	}

}
void EffectThunder ::Release()
{

}