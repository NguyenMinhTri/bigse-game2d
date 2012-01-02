#include "GodLike_Attack3.h"
#include "RSMainGame.h"
#include "Global.h"
#include "InfoSprite.h"
#include "ManagerObject.h"
#include "EffectSound.h"
#include "EffectFont.h"

GodLike_Attack3 ::GodLike_Attack3 (GodLike_Beast *_GodLike)
{
	m_GodLike = _GodLike ;
	Init() ;
}


GodLike_Attack3 ::~GodLike_Attack3 (void)
{
}

void GodLike_Attack3  ::Init()
{
	m_Damage = 1800;
	m_iCollision = false ;
	m_Attack1  = RSMainGame::get()->getGodLikeAttack3() ;
	m_InfoSprite1.setSize(717,603) ;

	setSize(717,603);
	m_STT = READY ;
	timeshoot = true;
}

void GodLike_Attack3  ::Active(float _X,float _Y,int _Dir)
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
		timeshoot = true ;
	}
}
void GodLike_Attack3  ::Animation(float _Time)
{
	if(m_STT == ACTIVE)
	{
		m_TimeAni +=_Time ;
		if(m_TimeAni >= 0.16f)
		{
			m_TimeAni -=0.16f;
			m_InfoSprite1.NextFrame(0,19) ;
			if(m_InfoSprite1.getCurFrame()>=8 && m_InfoSprite1.getCurFrame() <= 13 )
			{
				m_iCollision = true ;
			}
			if(m_InfoSprite1.getCurFrame() >=18 )
			{
				m_STT = COOLDOWN ;
				timeshoot = false ;
				m_TimeAni =0;
			}
		}
	}
}

void GodLike_Attack3 ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}

void GodLike_Attack3  ::UpdateStatus(float _Time)
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
void GodLike_Attack3  ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung


		EffectSound *m_EffectSound = new EffectSound(_Obj->getX(),_Obj->getY());
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectSound );

		EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - m_Damage );
		if(_Obj->getHp() == 0)
		{
			_Obj->setLife(false); 
		}	
	}
}

void GodLike_Attack3  ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_InfoSprite1.setScaleX(1);
	}else{
		m_InfoSprite1.setScaleX(-1);
	}
	m_InfoSprite1.setXY(m_X -30,m_Y);
	m_Attack1->Draw(_mtWorld,m_InfoSprite1,_Handler);
}

void GodLike_Attack3  ::Release()
{

}

