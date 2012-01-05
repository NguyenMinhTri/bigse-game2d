#include "SnakeMens_Effect1.h"
#include "RSMainGame.h"

SnakeMens_Effect1::SnakeMens_Effect1(float _X, float _Y)
{
	m_X=_X;m_Y=_Y;

	Init();
}


SnakeMens_Effect1::~SnakeMens_Effect1(void)
{
}

void SnakeMens_Effect1::Init()
{
	m_Sprite=RSMainGame::get()->getSnakeMans_Attack1_Hit();
	m_InfoSprite.setXY(200,135);
	m_InfoSprite.setScaleXY(2,2);
	m_InfoSprite.setDepth(0.3);
	m_iLife=true;
	m_TimeAni=0;

}
void SnakeMens_Effect1::Update(float _Time)
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
void SnakeMens_Effect1::Animation(float _Time)
{

}
void SnakeMens_Effect1::Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		/*		m_InfoSprite.setXY(-43.5+m_X,-120+m_Y);*/
		m_Sprite->Draw(_MWorld,m_InfoSprite,_Handler);
	}
}