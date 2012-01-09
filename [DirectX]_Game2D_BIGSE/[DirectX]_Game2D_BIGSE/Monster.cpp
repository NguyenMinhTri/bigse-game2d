#include "Monster.h"
#include "RSMainGame.h"
#include "Global.h"
#include "Frenzy.h"
#include "CallPet.h"
#include "Item.h"
#include "ManagerObject.h"
#include "EffectSystem.h"
#include "ElephantDie.h"
#include "EffectInfoEle.h"
#include "ItemSkull.h"
Monster::Monster(void)
{
	m_HP = 2100;
	Init();

}


Monster::~Monster(void)
{

}
void Monster::Init()
{
	v_x = g_GodLike_Beast ;
	setFrenzey(false);
	m_Direct = 1;
	m_STT = ACTIVE;
	m_ElephantMove = RSMainGame::get()->getElephantMove() ;
	m_InfoMove.setSize(128,120);
	m_InfoMove.setDepth(0.2);

	setSize(128,120);
	m_Hit = false;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new ElephantAttack(this));


}

void Monster::ActiveSkill(int _Index)
{
	m_skillManager->ActiveSkill(_Index,m_X,m_Y,m_Direct);
	if (m_Vy < 0) //nhay len
	{
		m_Vy = fabs (m_Vy);
	}
}
bool Monster::iCollision(MyObject* _Obj)
{
	return false;
}
void Monster ::setJump()
{
	if(m_Vy!= 0) return;
	m_Vy = -1* g_VY_JUMP;	
}
void Monster :: Move (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{

		float NextX, NextY ;
#pragma  region RIGHT 
	if(m_Direct > 0 )
	{
		NextX =m_X + _Time * v_x;

		if (NextX >= _MaxWidth - m_Width) 
		{
			NextX = _MaxWidth - m_Width;
			m_Direct =- 1;
		}
		bool iColTer = false;
		for (int i = (m_X + m_Width)/g_CELL ; i <  (NextX+m_Width)/g_CELL;i++)
		{
			for (int j = m_Y/g_CELL;j < (int)((m_Y+m_Height-1)/g_CELL) +1;j++ ){
				if (_Terrain[i][j]!=0){
					iColTer = true;
					m_X = g_CELL * (i) - m_Width;
					
					m_Direct = -1 ;
					break;
				}
			}
			if (iColTer == true)
			{
				m_Direct = -1 ;
				break;
			}
		}

		if (iColTer == false)
		{
			m_X = NextX;
		}
	}
#pragma  region LEFT
	else if(m_Direct <0)
	{
		NextX= m_X - _Time* v_x;
		if (NextX <= 0)
		{
			NextX = 0;
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

#pragma endregion LEFT

#pragma region DOWN
	m_Vy+= _Time*g_GRAVITY;
	NextY = m_Y + m_Vy*_Time/* + 0.5*(_Time*_Time)*g_GAVITY*/;
	if (NextY >= (_MaxHeight - m_Height))
	{
		NextY =  _MaxHeight - m_Height;
	}
	if (NextY <= 0)
	{
		NextY = 0;
		m_Vy = fabs(m_Vy);
	}

	if (m_Vy >= 0)
	{
		bool iColTer = false;
		 for (int j = (m_Y+m_Height)/g_CELL; j <  (NextY+m_Height)/g_CELL ;j++)
		 {
			for (int i = m_X/g_CELL;i < (m_X+m_Width)/g_CELL;i++ )
			{
				if (_Terrain[i][j]!=0)
				{
					iColTer = true;
					m_Y = g_CELL * (j) - m_Height;
					m_Vy = 0;
					break;
				}
			}
				if (iColTer == true)
				{
					break;
				}
		 }
		
		if (iColTer == false)
		{
			m_Y = NextY;
		}
	}
#pragma endregion DOWN

	}
void Monster::ProcessCollision(MyObject* _Obj)
{
	m_skillManager->ProcessCollision(_Obj);
	if(!getRect().iCollision(_Obj->getRect()))
	{
		if(abs(_Obj->getX() - m_X ) < 400 ) 
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
	if(abs(_Obj->getX() - m_X ) < 200 ) 
	{
		ActiveSkill(0);		
	}
}
void Monster::Animation(float _Time){
	m_TimeAni += _Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			if (m_Vy != 0)
			{
				m_InfoMove.setCurFrame(4);
			}
			else
			{
					m_InfoMove.NextFrame(0,7);
			}
		}
		break;
	}
}

void Monster::UpdateStatus(float _Time)
{
	if(getLife() == false)
	{
		ItemSkull *_itemSkull = new ItemSkull(m_X,m_Y);
		Item *_item = new Item(m_X,m_Y);
		int random ;
		random = rand() % 6 ;
		switch(random)
		{
		case  0 :
			ManagerObject::Instance()->getListItem()->push_back(_item);
			break ;
		case 1 :
			ManagerObject::Instance()->getListItem()->push_back(_itemSkull);
			break ;

		}

		ElephantDie *_EffectDie = new ElephantDie (m_X,m_Y);
		ManagerObject::Instance()->getListEffect()->push_back(_EffectDie);
	}
	if(!m_iActive )
	{
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 1 )
		{
			m_iActive = true ;
			m_TimeUpdate =0;
		}
	}
	if(getFrenzy() == true)
	{
			m_TimeUpdate += _Time;
			if(m_TimeUpdate > 1.95)
			{
				setFrenzey(false);
				m_TimeUpdate =0;
			}
	}
}

void Monster::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if(m_skillManager->getSkill(0)->getSTT()==ACTIVE)
	{
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
	else if(m_skillManager->getSkill(0)->getSTT() !=ACTIVE)
	{
		if(getFrenzy() ==false)
		{
	      	Move(_Time,_Terrain,_MaxWidth,_MaxHeight);	
		}
		Animation(_Time);
		UpdateStatus(_Time);
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight); //??
	}

}

void Monster::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
			if (m_skillManager->getSkill(0)->getSTT()==ACTIVE)
			{
				m_skillManager->getSkill(0)->Draw(_MWorld,_Handler) ;
			}
			if (m_Direct<0){
				m_InfoMove.setScaleX(1);
			}else{
				m_InfoMove.setScaleX(-1);
			}
			if (m_skillManager->getSkill(0)->getSTT()!=ACTIVE)
			{
				m_InfoMove.setXY(m_X,m_Y);
				m_ElephantMove->Draw(_MWorld,m_InfoMove,_Handler);
			}
}
void  Monster::Release(){
}
