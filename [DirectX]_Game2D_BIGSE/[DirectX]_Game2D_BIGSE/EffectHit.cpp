#include "EffectHit.h"
#include "RSMainGame.h"

EffectHit::EffectHit(float x,float y)
{
	m_X = x;
	m_Y = y;
	Init();
}


EffectHit::~EffectHit(void)
{

}
void EffectHit ::Init()
{
	m_InfoSprite.setSize(197,177);
	m_Sprite = RSMainGame::get()->getEffectHit();
	m_iLife = true;
    m_InfoSprite.setDepth(0.2);
	m_TimeAni =0;
}

void EffectHit::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.15f)
	{
		m_TimeAni -= 0.15f;			
		m_InfoSprite.NextFrame(0,5);
		if (m_InfoSprite.getCurFrame()>=4)
		{
			m_TimeAni = 0;
			m_iLife = false;
		}
	}		
}

void EffectHit ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		m_InfoSprite.setXY(m_X,m_Y);
		m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
	}
}

void EffectHit::Release()
{

}