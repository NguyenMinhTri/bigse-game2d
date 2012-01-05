#include "EffectInfoEle.h"
#include "RSMainGame.h"

EffectInfoEle::EffectInfoEle(float x,float y)
{
	m_X = x;
	m_Y = y;
    Init();
}


EffectInfoEle::~EffectInfoEle(void)
{

}
void EffectInfoEle ::Init()
{
	m_InfoSprite.setSize(178,139);
	m_Sprite = RSMainGame::get()->getElephantInfo();
	m_iLife = true;
	m_InfoSprite.setDepth(0.2);
	m_TimeAni =0;
}
void EffectInfoEle ::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.15f)
	{
		m_TimeAni -= 0.15f;			
		m_InfoSprite.NextFrame(0,3);
		if (m_InfoSprite.getCurFrame()>=2)
		{
			m_TimeAni = 0;
			m_iLife = false;
		}
	}	
}
void EffectInfoEle ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{		
	m_InfoSprite.setXY(m_X,m_Y );
    m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
}
void EffectInfoEle::Release()
{

}