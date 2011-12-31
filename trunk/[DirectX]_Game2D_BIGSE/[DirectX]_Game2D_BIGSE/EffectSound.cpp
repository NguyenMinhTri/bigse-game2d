#include "EffectSound.h"
#include "RSMainGame.h"

EffectSound::EffectSound(float x, float y)
{
	m_X = x;
	m_Y = y;
	Init();
}


EffectSound::~EffectSound(void)
{
}

void EffectSound ::Init()
{
	m_InfoSprite.setSize(151,151);
	m_Sprite = RSMainGame::get()->getEffectSound() ;
	m_iLife = true;
	m_TimeAni =0;
}

void EffectSound ::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.16f)
	{
		m_TimeAni -= 0.16f;			
		m_InfoSprite.NextFrame(0,3);
		if (m_InfoSprite.getCurFrame()>=2)
		{
			m_TimeAni = 0;
			m_iLife = false;
		}
	}		
}
void EffectSound :: Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		m_InfoSprite.setScaleXY(2.0f,2.0f);
		m_InfoSprite.setXY(m_X  - 30, m_Y);
		m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
	}
}

void EffectSound ::Release()
{

}