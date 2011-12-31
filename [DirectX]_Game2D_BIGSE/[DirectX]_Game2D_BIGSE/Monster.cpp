#include "Monster.h"
#include "RSMainGame.h"
#include "Global.h"
#include "Frenzy.h"
#include "CallPet.h"
#include "Item.h"
#include "ManagerObject.h"
#include "EffectSystem.h"

Monster::Monster(void)
{
	m_HP =10;
	Init();

}


Monster::~Monster(void)
{

}
void Monster::Init()
{
	setFrenzey(false);
	m_Direct = 1;
	count = 0 ;
	setSize(50,85);
	m_STT = ACTIVE;
	m_Monster = RSMainGame::get()->getCharacter();
	m_InfoSprite.setSize(300,200);
	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new Skill());
	m_skillManager->AddSkill(new CallPet());

// 	m_itemManager = new ItemManager();
// 	m_itemManager->AddItem(new Item());
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
		NextX =m_X + _Time * g_VX;

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
		NextX= m_X - _Time* g_VX;
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
	if(getLife() == true)
	{
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
        		ActiveSkill(0);		
				int a = m_X;
				if(m_X >a || m_X<a)
				{
					m_X = a ;
				}
		}
	}
// 	if(m_skillManager->getSkill(0)->getRect().iCollision(_Obj->getRect()))
// 	{
// 
// 		ActiveSkill(1);	
// 	}		
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
				m_InfoSprite.setCurFrame(4);
			}
			else
			{
					m_InfoSprite.NextFrame(0,4);
			}
		}
		break;
	}
}

void Monster::UpdateStatus(float _Time)
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
	if(getLife() == false)
	{
		EffectSystem *_EffectDie = new EffectSystem(m_X,m_Y);
		ManagerObject::Instance()->getListEffect()->push_back(_EffectDie);

		Item *_item = new Item(m_X,m_Y);
		ManagerObject::Instance()->getListItem()->push_back(_item);
	}

		Animation(_Time);
		if(getFrenzy() ==false)
		{
	      	Move(_Time,_Terrain,_MaxWidth,_MaxHeight);	
		}
		UpdateStatus(_Time);
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
}

void Monster::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(getLife() == true)
	{	
			m_skillManager->Draw(_MWorld,_Handler);

			if( getActive() ==false)
			{
				if (timeGetTime()%400 >200)
				{
					return ;
				}
			}

			if (m_skillManager->getSkill(0)->getSTT()==ACTIVE)
			{
				m_InfoSprite.setCurFrame(m_skillManager->getSkill(0)->getInfoSprite().getCurFrame());
			}

			if (m_Direct<0){
				m_InfoSprite.setScaleX(1);
			}else{
				m_InfoSprite.setScaleX(-1);
			}
			m_InfoSprite.setXY(-125+m_X,-54+m_Y);

			m_Monster->Draw(_MWorld,m_InfoSprite,_Handler);
	}

}
void  Monster::Release(){

}
