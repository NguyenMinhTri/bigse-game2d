#include "GodLike_Beast.h"
#include "Global.h"
#include "RSMainGame.h"
#include "InfoSprite.h"
#include "GodLike_Attack1.h"
#include "GodLike_Attack2.h"
#include "GodLike_Attack3.h"
#include "GodLike_Attack4.h"

GodLike_Beast::GodLike_Beast(void)
{
	m_HP = 10 ;
	Init() ;
}


GodLike_Beast::~GodLike_Beast(void)
{
}
void GodLike_Beast ::Init()
{
	m_Direct = 1 ;
	m_VMove = g_GodLike_Beast ;

	m_GodLike_Move = RSMainGame::get()->getGodLikeMove() ;
	m_GodLike_Stand = RSMainGame ::get()->getGodLikeStand() ;

	m_InfoSprite1.setSize(566,524) ; //move
	m_InfoSprite1.setDepth(0.4);

	m_InfoSprite2.setSize(554,509) ; //stand 
	m_InfoSprite2.setDepth(0.4) ;
	setSize(360,524) ;

	m_STT = ACTIVE ;
	g_STT = ACTIVE ;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new GodLike_Attack1(this)) ; //sam' set'
	m_skillManager->AddSkill(new GodLike_Attack2(this)) ; 
	m_skillManager->AddSkill(new GodLike_Attack3(this)) ; 
    m_skillManager->AddSkill(new GodLike_Attack4(this)) ; 

}
void GodLike_Beast ::ActiveSkill (int _Index )
{
	m_skillManager->ActiveSkill(_Index,m_X,m_Y,m_Direct);
}
void GodLike_Beast ::Animation(float _Time)
{
	m_TimeAni += _Time ;
	switch (m_STT)
	{
	   case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
				if (g_STT == READY)//Ready : Stand 
				{
					m_InfoSprite2.NextFrame(0,5);
					if(m_InfoSprite2.getCurFrame() ==5)
					{
						m_InfoSprite2.setCurFrame(0);
					}
				} 
				else if (g_STT == ACTIVE) //ACTIVE : Move
				{
					m_InfoSprite1.NextFrame(0,18);
					if(m_InfoSprite1.getCurFrame() ==17)
					{
						m_InfoSprite1.setCurFrame(0);
					}
				}
		}
		break ;
	}
}

void GodLike_Beast ::UpdateStatus(float _Time)
{
	if(!m_iActive )
	{
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 1 )
		{
			m_iActive = true ;
			m_TimeUpdate =0;
		}
	}
}

void GodLike_Beast :: Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	g_STT = ACTIVE ;
	float NextX,NextY;
#pragma region RIGHT
	if (m_Direct > 0)
	{
		m_X =m_X + _Time* m_VMove; //thoi gian thuc
		if (m_X >= _MaxWidth - m_Width)
		{
			m_X = _MaxWidth - m_Width;
			m_Direct = -1 ;
		}
	}
#pragma endregion RIGHT

#pragma  region LEFT
	if(m_Direct < 0)
	{
		m_X = m_X - _Time * m_VMove ;
		if (m_X <=0 )
		{
			m_X = 0;
			m_Direct = 1 ;
		}
	}
#pragma  endregion LEFT 
}
void GodLike_Beast ::ProcessCollision(MyObject* _Obj)
{
	if(getLife() == true)
	{
	if(!getRect().iCollision(_Obj->getRect()))
	{
		if(abs(_Obj->getX() - m_X ) < 1000 ) 
		{
			if(_Obj->getX() > m_X )
			{
				m_Direct =1 ;
			}
			if(_Obj->getX() < m_X)
			{
				m_Direct = -1 ;
			}
		}
	}
		m_skillManager->ProcessCollision(_Obj);
		if(getRect().iCollision(_Obj->getRect()))
		{
			if(_Obj->getDirection() > 0 && _Obj->getX() > m_X )
			{
				if(m_Direct <0)
				{
					m_Direct = 1 ;
					m_X = m_X + 50;
				}
			}
			else if(_Obj->getDirection() < 0 && _Obj->getX() < m_X )
			{
				if(m_Direct > 0)
				{
					m_Direct =-1 ;
					m_X = m_X + 60;
				}
			}
			if(!_Obj->getLife())
			{
				return ;
			}

			int a = m_X;
			if(m_X >a || m_X<a)
			{
				m_X = a ;
			}
		}
	}
}
							
void GodLike_Beast ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	m_TimeUpdate +=_Time ;

	int random ;
	random = rand() % 4;

	if(m_TimeUpdate > 2)
	{
	switch (random)
	{
	case 0:
		if(	m_skillManager->getSkill(1)->getSTT()!=ACTIVE  && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE )
			ActiveSkill(0);
		m_TimeUpdate = 0 ;
		break;
	case 1:
		if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE )
		   ActiveSkill(1);
		m_TimeUpdate = 0 ;
		break ;

	case 2:
		if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE )
			ActiveSkill(2);
		m_TimeUpdate = 0 ;
		break ;
	case 3:
		if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(2)->getSTT()!=ACTIVE )
			ActiveSkill(3) ;
		m_TimeUpdate = 0 ;
		break ;
		
		default : break ;
		}
	}
	if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE  )
	{
		Animation(_Time);
		Move(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
	m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight) ;
	UpdateStatus(_Time);
}

void GodLike_Beast::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(getLife() == false)
	{
		return ;
	}

	if (m_skillManager->getSkill(0)->getSTT()==ACTIVE)
	{
		m_skillManager->getSkill(0)->Draw(_MWorld,_Handler) ;
	}
	if (m_skillManager->getSkill(1)->getSTT()==ACTIVE )
	{
		m_skillManager->getSkill(1)->Draw(_MWorld,_Handler) ;
	}

	if (m_skillManager->getSkill(2)->getSTT()==ACTIVE )
	{
		m_skillManager->getSkill(2)->Draw(_MWorld,_Handler) ;
	}

	if (m_skillManager->getSkill(3)->getSTT()==ACTIVE )
	{
		m_skillManager->getSkill(3)->Draw(_MWorld,_Handler) ;
	}
	m_InfoSprite1.setXY(m_X, m_Y);
	m_InfoSprite2.setXY(m_X, m_Y);

	if (m_Direct>0)
	{
		m_InfoSprite1.setScaleX(-1);
		m_InfoSprite2.setScaleX(-1) ;
	}

	else if(m_Direct<0)
	{
		m_InfoSprite1.setScaleX(1);
		m_InfoSprite2.setScaleX(1);
	}

	if(m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE)
	{
		if(g_STT == ACTIVE)
		{
			m_GodLike_Move->Draw(_MWorld,m_InfoSprite1,_Handler);
		}
		if(g_STT == READY)
 		{
 			m_GodLike_Stand->Draw(_MWorld,m_InfoSprite2,_Handler) ;
		}
	}
}