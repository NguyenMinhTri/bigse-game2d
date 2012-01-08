#include "Pharaon.h"
#include "ManagerObject.h"
#include "EffectFont.h"
#include "RSMainGame.h"
#include "SoundGame.h"
Pharaon::Pharaon(Character *_Character)
{
	m_Character = _Character ;
	Init() ;
}
Pharaon::~Pharaon(void)
{
}
void Pharaon ::Init()
{
	m_Damage = 2000 ;
	m_iCollision = false ;
	m_Pharaon   = RSMainGame::get()->getPharaon() ;
	m_InfoSprite.setSize(1010,517) ;
	setSize(1010,517);
	m_STT = READY ;

}
void Pharaon ::Active(float _X,float _Y,int _Dir)
{
	if(m_STT ==READY ) //dang ready moi cho active 
	{
		if(_Dir >0 )
		{
			m_X = _X ;
			m_Y = _Y ;
			m_Direct = _Dir ;
		}
		if(_Dir < 0)
		{
			m_X = _X ;
			m_Y = _Y ;
			m_Direct =_Dir ;
		}
		m_TimeAni = 0;
		m_iCollision = false ;
		m_InfoSprite.setCurFrame(0);
		m_STT = ACTIVE ;
	}
}
void Pharaon ::Animation(float _Time)
{
	if(m_STT == ACTIVE)
	{
		SoundGame ::Instance()->PlayPharaon();
		m_TimeAni +=_Time ;
		if(m_TimeAni >= 0.16f)
		{
			m_TimeAni -=0.16f;
			m_InfoSprite.NextFrame(0,21) ;
			if(m_InfoSprite.getCurFrame()>=6 && m_InfoSprite.getCurFrame() <= 16 )
			{
				m_iCollision = true ;
			}
			if(m_InfoSprite.getCurFrame() >=20 )
			{
				m_STT = COOLDOWN ;
				m_TimeAni =0;
			}
		}
	}
}

void Pharaon::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}
void Pharaon ::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 1)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}
void Pharaon ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung

		EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);

		_Obj->m_iThunder = true ;

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - m_Damage );
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}
void Pharaon :: Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_Character->getDirection() >0 )
	{
		  m_InfoSprite.setXY( m_X , m_Y- 300);
	}
	if(m_Character->getDirection() < 0)
	{
	     m_InfoSprite.setXY( m_Character->getX() - 900,m_Y - 300 );
	}
	
	
	m_Pharaon->Draw(_mtWorld,m_InfoSprite,_Handler);
}

void Pharaon ::Release()
{

}
