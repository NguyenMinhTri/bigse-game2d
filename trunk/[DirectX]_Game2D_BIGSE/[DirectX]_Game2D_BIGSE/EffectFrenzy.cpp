#include "EffectFrenzy.h"
#include "RSMainGame.h"
#include "Global.h"

EffectFrenzy::EffectFrenzy(void)
{
}
EffectFrenzy::EffectFrenzy(float x, float y)
{
	m_X = x;
	m_Y = y;
	Init();
}

EffectFrenzy::~EffectFrenzy(void)
{
}
void EffectFrenzy::Init()
{
	m_Time = true ;
 	m_InfoSprite.setSize(137,155);
	m_Sprite = RSMainGame::get()->getEffectIce();
	m_iLife = true;
	m_TimeAni =0;
}
void EffectFrenzy::Update(float _Time)
{
	 	m_TimeAni += _Time ;	
	 	if (m_TimeAni>= 0.15f)
	 	{
	 		m_TimeAni -= 0.15f;			
			m_InfoSprite.NextFrame(0,14);
			if (m_InfoSprite.getCurFrame()>=13)
			{
	 			m_TimeAni = 0;
				m_iLife = false;
	 		}
	 	}		
}
void EffectFrenzy ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		m_InfoSprite.setXY(-43.5+m_X,-60+m_Y);
	    m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
	}
     
}
void EffectFrenzy ::Release()
{

}