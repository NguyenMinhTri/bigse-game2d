#include "GodLike_Attack4.h"
#include "GodLike_Beast.h"
#include "RSMainGame.h"
#include "InfoSprite.h"
#include "ManagerObject.h"
#include "EffectLaze.h"
#include "EffectFrenzy.h"
#include "EffectFont.h"


GodLike_Attack4::GodLike_Attack4(GodLike_Beast* _GodLike)
{

	m_GodLike = _GodLike ;
	Init() ;
}


GodLike_Attack4::~GodLike_Attack4(void)
{
}

void GodLike_Attack4 ::Init()
{
	m_Damage = 1600 ;
	count =0;
	m_Attack4_1 = RSMainGame::get()->getGodLikeAttack4_1() ;
	m_Attack4_2 = RSMainGame::get()->getGodLikeAttack4_2() ;

	t_STT = READY ;
	m_InfoSprite4_1.setSize(1346 , 639) ;
	m_InfoSprite4_2.setSize(1346 , 639) ;
	setSize(900,639);
	m_STT=READY;
}

void GodLike_Attack4::Active(float _X,float _Y,int _Dir)
{
	if (m_STT == READY) //chua tung skill
	{
		if (_Dir>0)
		{
			m_X = _X;
			m_Y = _Y;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X + 50- m_Width ;
			m_Y = _Y;
			m_Direct = _Dir;
		}		

		m_STT = ACTIVE;
		t_STT = READY ;
		m_InfoSprite4_1.setCurFrame(0);
		m_InfoSprite4_2.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
	}
}

void GodLike_Attack4 ::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.16f)
		{
			m_TimeAni-= 0.16f;
			if(t_STT== READY)
			   m_InfoSprite4_1.NextFrame(0,17);
			if(m_InfoSprite4_1.getCurFrame() >=16)
			{
				t_STT = ACTIVE ;
				if(t_STT == ACTIVE)
				{
					m_InfoSprite4_2.NextFrame(0,17) ;
					if(m_InfoSprite4_2.getCurFrame()>=0 && m_InfoSprite4_2.getCurFrame() <=10 )
					{
					   m_iCollision = true ;
					}
					if(m_InfoSprite4_2.getCurFrame() >=16)
					{
						m_TimeAni = 0;
						m_STT = COOLDOWN;
					}
				}
			}
		}
	}
}

void GodLike_Attack4 ::ProcessCollision(MyObject *_Obj)
{
		if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
		{
			if(_Obj->getActive() == false  )
			{
				return ;
			}//true la chua trung


			EffectLaze*m_EffectLaze = new EffectLaze(_Obj->getX(), _Obj->getY());
			ManagerObject::Instance()->getListEffect()->push_back(m_EffectLaze);

			EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
			ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);

			_Obj->setActive(false);
			_Obj->setHp(_Obj->getHp() - m_Damage );
			if(_Obj->getHp() <= 0)
			{
				_Obj->setLife(false); 
			}	
		}
}

void GodLike_Attack4::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 20)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}
void GodLike_Attack4 ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}

void GodLike_Attack4 :: Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct>0)
	{
		m_InfoSprite4_1.setXY(m_X - 380,m_Y);
		m_InfoSprite4_2.setXY(m_X - 380,m_Y);
		m_InfoSprite4_1.setScaleX(-1);
		m_InfoSprite4_2.setScaleX(-1) ;
	}

	else if(m_Direct<0)
	{
		m_InfoSprite4_1.setXY(m_X + 350,m_Y);
		m_InfoSprite4_2.setXY(m_X + 350,m_Y);
		m_InfoSprite4_1.setScaleX(1);
		m_InfoSprite4_2.setScaleX(1);
	}

	if(t_STT ==READY )
	{
		m_Attack4_1->Draw(_MWorld,m_InfoSprite4_1,_Handler);
	}
	else if(t_STT == ACTIVE)
	{
		m_Attack4_2->Draw(_MWorld,m_InfoSprite4_2,_Handler);
	}
}