#include "Hero_Effect2.h"
#include "RSMainGame.h"

Hero_Effect2::Hero_Effect2(float _X, float _Y)
{
	m_X=_X;m_Y=_Y;

	Init();
}


Hero_Effect2::~Hero_Effect2(void)
{
}

void Hero_Effect2::Init()
{
	m_Sprite=RSMainGame::get()->getHero_Effect2();
	m_InfoSprite.setXY(103,103);
	m_InfoSprite.setScaleXY(2,2);
	m_InfoSprite.setDepth(0.1);
	m_iLife=true;
	m_TimeAni=0;

}
void Hero_Effect2::Update(float _Time)
{

	m_TimeAni+=_Time;
	
		if(m_TimeAni>=0.15f)
		{
			m_TimeAni-0.15f;
			if(m_iLife==true)
			{
			m_InfoSprite.NextFrame(0,5);
			if(m_InfoSprite.getCurFrame()>=4)
			{
				m_iLife=false;
				m_TimeAni=0;
			}
		}

	}		
}
void Hero_Effect2::Animation(float _Time)
{

}
void Hero_Effect2::Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
/*		m_InfoSprite.setXY(-43.5+m_X,-120+m_Y);*/
		m_Sprite->Draw(_MWorld,m_InfoSprite,_Handler);
	}
}