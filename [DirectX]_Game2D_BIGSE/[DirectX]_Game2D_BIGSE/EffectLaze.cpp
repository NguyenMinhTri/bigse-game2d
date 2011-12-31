#include "EffectLaze.h"
#include "RSMainGame.h"

EffectLaze::EffectLaze(float x, float y)
{
	m_X = x;
	m_Y = y;
	Init() ;
}

EffectLaze::~EffectLaze(void)
{
}

void EffectLaze :: Init()
{
	m_InfoSprite.setSize(103,106);
	m_Sprite = RSMainGame::get()->getEffectLaze() ;
	m_iLife = true;
	m_TimeAni =0;
}
void EffectLaze ::Update(float _Time)
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

void EffectLaze :: Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	    m_InfoSprite.setScaleXY(2.0f,2.0f);
		m_InfoSprite.setXY(m_X - 30, m_Y);
		m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);

}
void EffectLaze ::Release()
{

}