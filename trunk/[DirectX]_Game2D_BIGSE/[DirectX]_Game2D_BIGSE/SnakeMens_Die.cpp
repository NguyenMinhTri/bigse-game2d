#include "SnakeMens_Die.h"
#include "RSMainGame.h"

SnakeMens_Die::SnakeMens_Die(float _X, float _Y)
{
	m_X=_X;m_Y=_Y;

	Init();
}


SnakeMens_Die::~SnakeMens_Die(void)
{
}

void SnakeMens_Die::Init()
{
	m_Sprite=RSMainGame::get()->getSnakeMans_Die();
	m_InfoSprite.setSize(312,421);
	m_InfoSprite.setDepth(0.3f);
	m_iLife=true;
	m_TimeAni=0;

}
void SnakeMens_Die::Update(float _Time)
{
	m_TimeAni+=_Time;

	if(m_TimeAni>=0.1f)
	{
		m_TimeAni-=0.1f;
		if(m_iLife==true)
		{
			m_InfoSprite.NextFrame(0,39);
			if(m_InfoSprite.getCurFrame()>=38)
			{
				m_iLife=false;
				m_TimeAni=0;
			}
		}
	}
}
void SnakeMens_Die::Animation(float _Time)
{

}
void SnakeMens_Die::Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		m_InfoSprite.setXY(m_X,m_Y);
		m_Sprite->Draw(_MWorld,m_InfoSprite,_Handler);
	}
}