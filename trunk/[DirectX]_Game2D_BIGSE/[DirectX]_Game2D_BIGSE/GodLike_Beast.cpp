#include "GodLike_Beast.h"
#include "Global.h"
#include "RSMainGame.h"
#include "InfoSprite.h"
#include "GodLike_Attack1.h"
#include "GodLike_Attack2.h"
#include "GodLike_Attack3.h"
#include "GodLike_Attack4.h"
#include "ManagerObject.h"
#include "EffectLeonDie.h"
#include "GodLike_Teleport.h"

GodLike_Beast::GodLike_Beast(void)
{

	Init() ;
}


GodLike_Beast::~GodLike_Beast(void)
{
}

void GodLike_Beast ::Init()
{
	/*m_VxDirect = 0;*/
	m_Direct = 1 ;
	m_VMove = g_GodLike_Beast ;
	m_HP = 40000 ;
	m_iActive = true ;

	m_TimePrivate = 0;
	m_time = 0;

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
	m_skillManager->AddSkill(new GodLike_Attack1(this)) ; 
	m_skillManager->AddSkill(new GodLike_Attack2(this)) ; 
	m_skillManager->AddSkill(new GodLike_Attack3(this)) ; 
	m_skillManager->AddSkill(new GodLike_Attack4(this)) ; 
	m_skillManager->AddSkill(new GodLike_Teleport(this)) ; 

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
			if (g_STT == READY || m_VxDirect == 0 )//Ready : Stand 
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
		m_time+= _Time;
		if(m_time > 1 )
		{
			m_iActive = true ;
			m_time =0;
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
		bool iColTer = false;
		for (int i = (m_X + m_Width)/g_CELL ; i <  (NextX+m_Width)/g_CELL;i++)
		{
			for (int j = m_Y/g_CELL;j < (int)((m_Y+m_Height-1)/g_CELL) +1;j++ ){
				if (_Terrain[i][j]!=0){
					iColTer = true;
					m_X = g_CELL * (i) - m_Width;
					m_Direct = -1; 
					break;
				}
			}
			if (iColTer == true){
				m_Direct = -1 ;
				break;
			}
		}

		if (iColTer == false){
			m_X = NextX;
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
			m_Direct = 1;
		}
		bool iColTer = false;
		for (int i = m_X/g_CELL-1; i >  NextX/g_CELL-1;i--) // 
		{
			for (int j = m_Y/g_CELL ;j < int((m_Y+m_Height-1)/g_CELL) +1 ; j++ )
			{
				if (_Terrain[i][j]!=0){
					iColTer = true;
					m_X = g_CELL * (i+1);
					m_Direct = 1;
					break;
				}
			} 
			if (iColTer == true)
			{
				m_Direct =1;
				break;
			}
		}

		if (iColTer == false)
		{
			m_X = NextX;
		}
	}
#pragma  endregion LEFT 

	// #pragma  region STAND 
	// 	if(m_VxDirect == 0 || m_Direct == 0)
	// 	{
	// 		m_X = m_X ;
	// 		g_STT = READY ;
	// 	}
	// #pragma  endregion STAND 
}

void GodLike_Beast ::ProcessCollision(MyObject* _Obj)
{
	m_skillManager->ProcessCollision(_Obj);

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
			// 		if(abs(_Obj->getX() - m_X ) > 1000 ) 
			// 		{
			// 			if(	m_skillManager->getSkill(1)->getSTT()!=ACTIVE  && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE&& m_skillManager->getSkill(0)->getSTT()!=ACTIVE )
			// 				ActiveSkill(4);
			// 
			// 		}
		}

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
		}
	}
}

void GodLike_Beast ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if(getLife() == false)
	{
		EffectLeonDie *_EffectDie = new EffectLeonDie (m_X,m_Y);
		ManagerObject::Instance()->getListEffect()->push_back(_EffectDie);
		return ;
	}

	int random ;
	random = rand() % 4;	
	m_TimeUpdate+=_Time ;

	if(m_TimeUpdate > 2)
	{
		switch (random)
		{
		case 0:
			if(	m_skillManager->getSkill(1)->getSTT()!=ACTIVE  && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE&& m_skillManager->getSkill(4)->getSTT()!=ACTIVE )
				ActiveSkill(0);
			m_TimeUpdate= 0 ;
			break;
		case 1:
			if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE && m_skillManager->getSkill(4)->getSTT()!=ACTIVE  )
				ActiveSkill(1);
			m_TimeUpdate = 0 ;
			break ;
		case 2:
			if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE && m_skillManager->getSkill(4)->getSTT()!=ACTIVE )
				ActiveSkill(2);
			m_TimeUpdate = 0 ;
			break ;
		case 3:
			if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(4)->getSTT()!=ACTIVE  )
				ActiveSkill(3) ;
			m_TimeUpdate = 0 ;
			break ;

		}
	}
	if(	m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE && m_skillManager->getSkill(4)->getSTT()!=ACTIVE   )
	{
		Animation(_Time);
		Move(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
	m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight) ;
	UpdateStatus(_Time);
}

void GodLike_Beast::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{

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
	for(int i=0 ; i<=4 ;i++ )
	{
		if (m_skillManager->getSkill(i)->getSTT()==ACTIVE )
		{
			// 			if(m_skillManager->getSkill(4)->getSTT()==ACTIVE )
			// 			{ 
			// 					m_InfoSprite1.setXY(m_skillManager->getSkill(4)->getX(),m_skillManager->getSkill(4)->getY() ) ;
			// 					m_InfoSprite2.setXY(m_skillManager->getSkill(4)->getX(),m_skillManager->getSkill(4)->getY() ) ;
			// 			}
			m_skillManager->getSkill(i)->Draw(_MWorld,_Handler) ;
		}
	}

	if(m_skillManager->getSkill(0)->getSTT()!=ACTIVE  && m_skillManager->getSkill(1)->getSTT()!=ACTIVE && m_skillManager->getSkill(2)->getSTT()!=ACTIVE && m_skillManager->getSkill(3)->getSTT()!=ACTIVE && m_skillManager->getSkill(4)->getSTT()!=ACTIVE)
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