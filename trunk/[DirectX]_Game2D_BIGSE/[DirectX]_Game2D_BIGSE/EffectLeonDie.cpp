#include "EffectLeonDie.h"
#include "RSMainGame.h"

EffectLeonDie::EffectLeonDie(float x, float y)
{
	m_X = x;
	m_Y = y;
	Init();
}


EffectLeonDie::~EffectLeonDie(void)
{

}
void EffectLeonDie ::Init()
{
	m_InfoSprite1.setSize(2928,3500);
	m_InfoSprite2.setSize(2928,3500);

	m_VonLeon1 = RSMainGame::get()->getEffectLeonDie_1() ;
	m_VonLeon2 = RSMainGame::get()->getEffectLeonDie_2() ;
	m_iLife = true ;
	e_STT = READY;
	m_TimeAni = 0 ; 
}
void EffectLeonDie ::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.12f)
	{
		m_TimeAni -= 0.12f;	
		if(e_STT==READY)
			m_InfoSprite1.NextFrame(0,17);
		if(m_InfoSprite1.getCurFrame() >=16)
		{
			e_STT = ACTIVE ;
			if(e_STT == ACTIVE)
			{
				m_InfoSprite2.NextFrame(0,19);
				if(m_InfoSprite2.getCurFrame() >=18)
				{
					m_TimeAni =0;
					m_iLife = false ;
				}
			}
		}
	}
}
void EffectLeonDie ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		m_InfoSprite1.setXY(m_X,m_Y);
		m_InfoSprite2.setXY(m_X,m_Y);
	}
	if (m_Direct<0)
	{
		m_InfoSprite1.setScaleX(1);
	}
	else
	{
		m_InfoSprite2.setScaleX(-1);
	}
	if(e_STT ==READY)
	{
	      m_VonLeon1->Draw(_mtWorld,m_InfoSprite1,_Handler);
	}
	else if(e_STT ==ACTIVE)
	{
	       m_VonLeon2->Draw(_mtWorld,m_InfoSprite2,_Handler);
	}

}
void EffectLeonDie ::Release()
{

}