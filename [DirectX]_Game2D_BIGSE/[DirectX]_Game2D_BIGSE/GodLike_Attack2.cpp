#include "GodLike_Attack2.h"
#include "RSMainGame.h"

GodLike_Attack2::GodLike_Attack2(GodLike_Beast *_GodLike)
{
	m_GodLike = _GodLike ;
	Init() ;
}



GodLike_Attack2::~GodLike_Attack2(void)
{
}


void GodLike_Attack2 ::Init()
{
	m_Damage = 1;
	m_iCollision = false ;
	m_Attack2  = RSMainGame::get()->getGodLikeAttack2() ;
	m_InfoSprite2.setSize(987,732) ;
	setSize(987,732);
	m_STT = READY ;
	timeshoot = true ;
}
void GodLike_Attack2 ::Active(float _X,float _Y,int _Dir)
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
		m_InfoSprite2.setCurFrame(0);
		m_STT = ACTIVE ;
		timeshoot = true  ;
	}
}
void GodLike_Attack2 ::Animation(float _Time)
{
	if(m_STT == ACTIVE)
	{
		m_TimeAni +=_Time ;
		if(m_TimeAni >= 0.16f)
		{
			m_TimeAni -=0.16f;
			m_InfoSprite2.NextFrame(0,19) ;
			if(m_InfoSprite2.getCurFrame()>=11 && m_InfoSprite2.getCurFrame() <= 15 )
			{
				m_iCollision = true ;
			}
			if(m_InfoSprite2.getCurFrame() >=18 )
			{
				m_STT = COOLDOWN ;
				m_TimeAni =0;
				timeshoot = false ;
			}
		}
	}
}
void GodLike_Attack2::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}


void GodLike_Attack2 ::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 4)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}
void GodLike_Attack2 ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - m_Damage );
		if(_Obj->getHp() == 0)
		{
			_Obj->setLife(false); 
		}	
	}
}
void GodLike_Attack2 ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_InfoSprite2.setScaleX(1);
	}else{
		m_InfoSprite2.setScaleX(-1);
	}
	m_InfoSprite2.setXY(m_X - 215,m_Y - 100);
	m_Attack2->Draw(_mtWorld,m_InfoSprite2,_Handler);
}
void GodLike_Attack2 ::Release()
{

}

