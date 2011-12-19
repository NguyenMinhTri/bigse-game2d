#include "Thunder.h"
#include "RSMainGame.h"
#include "Global.h"
#include "InfoSprite.h"
Thunder::Thunder(void)
{
	Init();
}


Thunder::~Thunder(void)
{

}
void Thunder::Init()
{
	m_iCollision = false;
	m_Damage = 1;
	m_STT = READY;
	t_STT = READY ;
	m_InfoThunder1.setSize(1199,598);
	m_InfoThunder2.setSize(1199,598);
	
	setSize(1199,598);
	m_Thunder1 = RSMainGame::get()->getThunder1();
	m_Thunder2 = RSMainGame::get()->getThunder2();
}

void Thunder::Active (float _X,float _Y,int _Dir)
{
	if (m_STT == READY) 
	{
		if (_Dir>0)
		{
			m_X = _X - 500 ;
			m_Y = _Y -500;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X + 500 ;
			m_Y = _Y - 500  ;
			m_Direct = _Dir;
		}

		m_STT = ACTIVE;
		t_STT = READY ;
		m_InfoThunder1.setCurFrame(0);	
		m_InfoThunder2.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false ;
	}
}
void Thunder::Animation(float _Time){
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			if(t_STT ==READY)
			m_InfoThunder1.NextFrame(0,18);
			if(m_InfoThunder1.getCurFrame() >=17)
			{
				t_STT = ACTIVE ;
				if(t_STT == ACTIVE )
				{
					m_InfoThunder2.NextFrame(0,18);
					if(m_InfoThunder2.getCurFrame() >=8 && m_InfoThunder2.getCurFrame()<=11)
					{
						m_iCollision = true ;
					}
					if(m_InfoThunder2.getCurFrame() >=17)
					{
						m_STT = COOLDOWN;
						m_TimeAni=0;
					}
				}
			}
		}
	}
}
void Thunder::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 1)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}
void Thunder ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}
void Thunder :: Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	m_InfoThunder1.setXY(m_X,m_Y);
	m_InfoThunder2.setXY(m_X,m_Y);

	if(t_STT ==READY )
	{
	     m_Thunder1->Draw(_MWorld,m_InfoThunder1,_Handler);
	}
	else if(t_STT == ACTIVE)
	{
		m_Thunder2->Draw(_MWorld,m_InfoThunder2,_Handler);
	}
}