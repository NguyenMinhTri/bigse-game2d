#include "Pet_Hero.h"
#include "MyObject.h"
#include "RSMainGame.h"
#include "Global.h"
#include "ManagerObject.h"
#include "Monster.h"
#include "MyObject.h"
#include "EffectFont.h"
Pet_Hero ::Pet_Hero(MyObject*  _Character)
{
	Init();
	m_Character =  _Character ;
}

Pet_Hero::~Pet_Hero(void)
{

}

void Pet_Hero :: Init()
{
	m_VMove=150;
	m_TimeLife=10;
	m_VFly=10;
	m_TimeCoolDown=2;
	p_stt=P_HIDE;
	m_Sprite_Move=RSMainGame::get()->getPet_Move();
	m_InfoSprite_Move.setSize(126,170);
	m_Sprite_GoAndBack=RSMainGame::get()->getPet_GoAndBack();
	m_Sprite_GoAndBack->SetSize(126,202);
	m_Sprite_Attack=RSMainGame::get()->getPet_Attack();
	m_InfoSprite_Attack,setSize(262,226);
}

void Pet_Hero ::Active()
{
	if(p_stt==P_HIDE)
	{
		p_stt=P_MOVE;
		setXY(m_Character->getX(),m_Character->getY()-200);
		m_InfoSprite_Move.setCurFrame(0);
		m_Sprite_Pet=m_Sprite_Move;
		m_InfoSprite_Pet=m_InfoSprite_Move;
	}
	else
		ActiveSkill(100,100);
}
void Pet_Hero::GO()
{

}
void Pet_Hero ::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight )
{
	if(p_stt!=P_MOVE)
		return;
	if(m_Character->getX()>=m_X+100)
	{
		m_Direct=-1;
		m_X+=_Time* m_VMove;
	}
	if(m_Character->getX()<=m_X-100)
	{
		m_Direct=+1;
		m_X-=_Time* m_VMove;
	}
	if(m_Character->getX()<=m_X
		&&m_Character->getX()+m_Character->getWidth()>=m_X)
	{
		m_Direct=-1*m_Character->getDirection();
	}
	if(m_Y>m_Character->getY()-120)
	{
		m_Y-=_Time* m_VMove;
	}
	if(m_Y<m_Character->getY()-120)
	{
		m_Y+=_Time* m_VMove;
	}
}

void Pet_Hero :: Animation(float _Time)
{
	m_TimeAni += _Time ;
	if(m_TimeAni>=0.1)
	{
		m_TimeAni-=0.1f;
		if(p_stt==P_MOVE)
		{
			m_InfoSprite_Move.NextFrame(0,4);
			
			if(m_InfoSprite_Move.getCurFrame()>=4)
			{
				m_InfoSprite_Move.setCurFrame(0);
			}
			m_Sprite_Pet=m_Sprite_Move;
			m_InfoSprite_Pet=m_InfoSprite_Move;
			m_InfoSprite_Pet.setXY(m_X,m_Y);
		}
		if(p_stt==P_BACK)
		{
			m_InfoSprite_GoAndBack.NextFrame(5,10);

			if(m_InfoSprite_GoAndBack.getCurFrame()>=9)
			{
				m_InfoSprite_GoAndBack.setCurFrame(0);
				p_stt=P_MOVE;
				return;
			}
			m_Sprite_Pet=m_Sprite_GoAndBack;
			m_InfoSprite_Pet=m_InfoSprite_GoAndBack;
			if(m_Direct<0)
			{
				m_InfoSprite_Pet.setXY(m_X+100,m_Y);
			}
			else
			{
				m_InfoSprite_Pet.setXY(m_X,m_Y);
			}
		}
		if(p_stt==P_GO)
		{
			m_InfoSprite_GoAndBack.NextFrame(5,10);

			if(m_InfoSprite_GoAndBack.getCurFrame()>=9)
			{
				m_InfoSprite_GoAndBack.setCurFrame(0);
				p_stt=p_ACTIVE;
				return;
			}
			m_Sprite_Pet=m_Sprite_GoAndBack;
			m_InfoSprite_Pet=m_InfoSprite_GoAndBack;
			if(m_Direct<0)
			{
				m_InfoSprite_Pet.setXY(m_X+100,m_Y);
			}
			else
			{
				m_InfoSprite_Pet.setXY(m_X,m_Y);
			}
		}
		if(p_stt==p_ACTIVE)
		{
			m_InfoSprite_Attack.NextFrame(0,10);
			
			if(m_InfoSprite_Attack.getCurFrame()>=2)
			{
				m_InfoSprite_Attack.setCurFrame(0);
				p_stt=P_BACK;
				return;
			}

			m_Sprite_Pet=m_Sprite_Attack;
			m_InfoSprite_Pet=m_InfoSprite_Attack;
			if(m_InfoSprite_Attack.getCurFrame()<=4)
			if(m_Direct<0)
			{
				
				m_InfoSprite_Pet.setXY(m_X+250,m_Y);
			}
			else
			{
				m_InfoSprite_Pet.setXY(m_X-200,m_Y);
			}
		}
	}
	
}
void Pet_Hero ::UpdateStatus(float _Time)
{
	
}

void Pet_Hero :: ProcessCollision(MyObject* _Obj)
{
	
}

void Pet_Hero ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	AutoSkill(_Time);
	Animation(_Time);
	Move(_Time,_Terrain,_MaxWidth,_MaxHeight);
}

void Pet_Hero::ActiveSkill(float _X,float _Y)
{
	if(p_stt!=P_MOVE)
		return;
		p_stt=P_GO;
}
void Pet_Hero::AutoSkill(float _Time)
{
	if(p_stt==P_HIDE)
		return;
	m_TimeUpdate+=_Time ;

	if(m_TimeUpdate > 5)
	{
		m_TimeUpdate-=5;
		int random;
		for(int i=0;i<ManagerObject::Instance()->getListMonster()->size();i++)
		{
			MyObject * temp;
			temp=ManagerObject::Instance()->getListMonster()->at(i);
			if((m_Y-(temp->getY()+temp->getHeight())<=150)&&temp->getX()>m_X-100&&getX()<m_X+200)
			{
				temp->setHp(temp->getHp()-300);
				EffectFont* m_EffectFont = new EffectFont(temp->getX(), temp->getY(),500);
				ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
				if(temp->getX()>m_X)
					m_Direct=-1;
				else
					m_Direct=1;
				ActiveSkill(m_X,m_Y);
				return;
			}

		}
	}
}

void Pet_Hero :: Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(p_stt==P_HIDE)
	{
		return;
	}
	else
	{
		m_InfoSprite_Pet.setScaleX(m_Direct);
		m_Sprite_Pet->Draw(_MWorld,m_InfoSprite_Pet,_Handler);
	}
}