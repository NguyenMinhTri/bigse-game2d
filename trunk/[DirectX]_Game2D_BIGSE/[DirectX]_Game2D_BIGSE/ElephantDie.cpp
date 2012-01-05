#include "ElephantDie.h"
#include "RSMainGame.h"

ElephantDie::ElephantDie(float x, float y)
{
	m_X = x;
	m_Y = y;
	Init();
}


ElephantDie::~ElephantDie(void)
{
}
void ElephantDie ::Init()
{
	m_InfoSprite.setSize(178,139);
	m_Sprite = RSMainGame::get()->getElephantDie();
	m_iLife = true;
	m_InfoSprite.setDepth(0.2);
	m_TimeAni =0;
}
void ElephantDie ::Update(float _Time)
{

	m_TimeAni += _Time ;	
	if (m_TimeAni>= 0.15f)
	{
		m_TimeAni -= 0.15f;			
		m_InfoSprite.NextFrame(0,12);
		if (m_InfoSprite.getCurFrame()>=11)
		{
			m_TimeAni = 0;
			m_iLife = false;
		}
	}		
}
void ElephantDie ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{

		m_InfoSprite.setXY(m_X,m_Y - 10);
		m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
}

void ElephantDie ::Release()
{

}