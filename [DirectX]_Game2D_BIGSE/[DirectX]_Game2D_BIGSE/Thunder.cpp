#include "Thunder.h"
#include "RSMainGame.h"
#include "Global.h"
#include "InfoSprite.h"
#include "ManagerObject.h"
#include "EffectFont.h"
Thunder::Thunder(void)
{
	Init();
}


Thunder::~Thunder(void)
{

}
Thunder::Thunder(MyObject *_Character)
{
	m_Character = _Character;
	Init();
}
void Thunder::Init()
{
	m_iCollision = false;
	m_Damage = 3000;
	m_STT = READY;
	time = READY ;
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
			m_Y = _Y - 500;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X - 500;
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
		time = TIME ;
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
						time = READY;
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
void Thunder ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}

		EffectFont* m_EffectFont = new EffectFont(m_X + 300,m_Y + 250,m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - m_Damage );
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}
void Thunder ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
// 	float _objectx = m_Character->getX();
// 	float _objecty = m_Character->getY();	
// 	if(m_Character->getX() != _objectx)
// 	{
// 		m_Character->setX(_objectx);
// 	}
// 	if(m_Character->getY() != _objecty)
// 	{
// 		m_Character->setY(_objecty);
// 	}
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