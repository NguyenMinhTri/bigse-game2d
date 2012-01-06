#include "EffectDieBear.h"
#include "RSMainGame.h"

EffectDieBear::EffectDieBear(Character* _Character ,float x, float y)
{
	m_Character = _Character ;
	m_X = x;
	m_Y = y;
	Init() ;
}

EffectDieBear::~EffectDieBear(void)
{

}
void EffectDieBear ::Init()
{
	m_InfoSprite.setSize(146,95);
	m_Sprite = RSMainGame::get()->getBearDie();
	m_iLife = true;
	m_TimeAni =0;
}

void EffectDieBear::Update(float _Time)
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
void EffectDieBear ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_Character->getDirection() > 0)
	{
		m_InfoSprite.setScaleX(-1);
	}
	if(m_Character->getDirection() < 0)
	{
		m_InfoSprite.setScaleX(1);
	}
	m_InfoSprite.setXY(m_X,m_Y);
	m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
}
void EffectDieBear ::Release()
{
}