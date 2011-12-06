#include "Arrow.h"
#include "Global.h"
#include "RSMainGame.h"


Arrow::Arrow(void)
{
	Init();
}


Arrow::~Arrow(void)
{
}
void Arrow::Init(){
	m_Damage = 1;
	m_STT = READY;
	m_InfoSprite.setSize(232,67);
	setSize(225,50);
	setShoot(false);
	m_SSkill = RSMainGame::get()->getArrow();

	m_Gravity = 0;
	m_Vx = 1000;
}
void Arrow::Active (float _X,float _Y,int _Dir)
{
	if(m_STT == READY)
	{
		if (_Dir>0)
		{
			m_X = _X;
			m_Y = _Y;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X + 50 - m_Width ;
			m_Y = _Y;
			m_Direct = _Dir;
		}
		m_TimeAni = 0;	
		m_STT = ACTIVE;
		m_InfoSprite.setCurFrame(0);
	}
}
void Arrow::Animation(float _Time)
{

	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_InfoSprite.NextFrame(0,13);
			if(m_InfoSprite.getCurFrame() >0 && m_InfoSprite.getCurFrame() <3)
			{
				setShoot(true);
			}
			
		}
	}

}
void Arrow::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case ACTIVE:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 2)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}
void Arrow::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){
	Animation(_Time);
	UpdateStatus(_Time);
	if(m_InfoSprite.getCurFrame() > 3  )
	{
		setShoot(false);
		m_VxDirect = m_Direct;
		MyObject::Move(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
	if (m_InfoSprite.getCurFrame()>13)
	{				
		m_STT = READY;
		m_TimeAni =0;

	}
}

void Arrow::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY( m_X,m_Y);
	m_SSkill->Draw(_MWorld,m_InfoSprite,_Handler);
}
