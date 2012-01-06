#include "GodLike_Attack1.h"
#include "RSMainGame.h"
#include "Global.h"
#include "InfoSprite.h"
#include "ManagerObject.h"
#include "EffectThunder.h"
#include "EffectFont.h"
GodLike_Attack1::GodLike_Attack1(GodLike_Beast *_GodLike)
{
	m_GodLike = _GodLike ;
	Init() ;
}


GodLike_Attack1::~GodLike_Attack1(void)
{
}
GodLike_Attack1::GodLike_Attack1(void)
{
	Init();
}
void GodLike_Attack1 ::Init()
{
	m_Damage = 1400;
	m_iCollision = false ;
	m_Attack1  = RSMainGame::get()->getGodLikeAttack1() ;
	m_InfoSprite1.setSize(802,607) ;

	setSize(780,647);
	m_STT = READY ;
}

void GodLike_Attack1 ::Active(float _X,float _Y,int _Dir)
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
		m_InfoSprite1.setCurFrame(0);
		m_STT = ACTIVE ;

	}
}
void GodLike_Attack1 ::Animation(float _Time)
{
	if(m_STT == ACTIVE)
	{
		m_TimeAni +=_Time ;
		if(m_TimeAni >= 0.16f)
		{
			m_TimeAni -=0.16f;
			m_InfoSprite1.NextFrame(0,23) ;
			    if(m_InfoSprite1.getCurFrame()>=10 && m_InfoSprite1.getCurFrame() <= 16 )
				{
					m_iCollision = true ;
				}
				if(m_InfoSprite1.getCurFrame() >=22 )
				{
					m_STT = COOLDOWN ;
					timeshoot = false ;
					m_TimeAni =0;
				}
		}
	}
}

void GodLike_Attack1::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}

void GodLike_Attack1 ::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 20)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}
void GodLike_Attack1 ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung

		EffectThunder*m_EffectThunder = new EffectThunder(_Obj->getX(), _Obj->getY());
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectThunder);

		EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);

		_Obj->m_iThunder = true ;

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - m_Damage );
		if(_Obj->getHp() == 0)
		{
			_Obj->setLife(false); 
		}	
	}
}

void GodLike_Attack1 ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_InfoSprite1.setScaleX(1);
			m_InfoSprite1.setXY(m_X - 110 ,m_Y - 60);
	}else{
		m_InfoSprite1.setScaleX(-1);
	   m_InfoSprite1.setXY(m_X  - 40,m_Y - 60);
	}

	m_Attack1->Draw(_mtWorld,m_InfoSprite1,_Handler);
}

void GodLike_Attack1 ::Release()
{

}

