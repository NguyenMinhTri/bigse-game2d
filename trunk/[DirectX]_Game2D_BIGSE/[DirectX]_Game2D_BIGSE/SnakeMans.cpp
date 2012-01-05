#include "SnakeMans.h"
#include "ManagerObject.h"
#include "SnakeMens_Attack1.h"
#include "SnakeMens_Attack2.h"
#include "SnakeMens_Attack4.h"
#include "SnakeMens_Attack3.h"
#include "SnakeMens_Die.h"
SnakeMans::SnakeMans(void)
{
	Init();
}


SnakeMans::~SnakeMans(void)
{
}
void SnakeMans::Init()
{
	m_SCharater= RSMainGame ::get()->getSnakeMans_Move();
	m_InfoSprite.setSize(202,269);
	m_InfoSprite.setDepth(0.3f);
	setSize(202,269);
	m_STT = ACTIVE ;
	m_VMove=50;
	m_HP=60000;
	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new SnakeMens_Attack1(this));
	m_skillManager->AddSkill(new SnakeMens_Attack2(this));
	m_skillManager->AddSkill(new SnakeMens_Attack3(this));
	m_skillManager->AddSkill(new SnakeMens_Attack4(this));
}

void SnakeMans::Animation(float _Time)
{
	m_TimeAni += _Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;

				if (m_Vy != 0 )
				{
					m_InfoSprite.NextFrame(0,5);
					if(m_InfoSprite.getCurFrame() >4)
					{
						m_InfoSprite.setCurFrame(0);
					}
				}
				else{
					if (m_VxDirect == 0){
						m_InfoSprite.NextFrame(0,5);
					} 
					else{
						m_InfoSprite.NextFrame(0,5);

					}
				}				
		}
		break;
	}
}
void SnakeMans::ActiveSkillAuto(float _Time)
{
	m_TimeUpdate+=_Time ;

	if(m_TimeUpdate > 2)
	{
		int random;
		if(ManagerObject::Instance()->getObjectCamera()->at(0)->getX()>=m_X+500||ManagerObject::Instance()->getObjectCamera()->at(0)->getX()<=m_X-500)
		{
			random = rand() % 2;
			ActiveSkill(random);
		}else
		if(ManagerObject::Instance()->getObjectCamera()->at(0)->getX()<=m_X
			&&ManagerObject::Instance()->getObjectCamera()->at(0)->getX()+ManagerObject::Instance()->getObjectCamera()->at(0)->getWidth()>=m_X)
		{
			random=rand()%2;
			ActiveSkill(random+2);
		}
		else
		{
			random=rand()%4;
			ActiveSkill(random);
		}
		m_TimeUpdate-=2;
	}
}
void SnakeMans::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if(getLife()==false)
	{
		if (m_Direct<0)
		{
			SnakeMens_Die *_SnakeMens_Die = new SnakeMens_Die(m_X-50,m_Y-50);
			_SnakeMens_Die->m_InfoSprite.setScaleX(1);

			ManagerObject::Instance()->getListEffect()->push_back(_SnakeMens_Die);
		}
		else
		{
			SnakeMens_Die *_SnakeMens_Die = new SnakeMens_Die(m_X-100,m_Y-50);
			_SnakeMens_Die->m_InfoSprite.setScaleX(-1);

			ManagerObject::Instance()->getListEffect()->push_back(_SnakeMens_Die);
		}
	}
	else
	if(m_skillManager->getSkill(0)->getSTT()==ACTIVE||
		m_skillManager->getSkill(1)->getSTT()==ACTIVE||
		m_skillManager->getSkill(2)->getSTT()==ACTIVE||
		m_skillManager->getSkill(3)->getSTT()==ACTIVE)
	{
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
	else
	{
		UpdateStatus(_Time);
		Animation(_Time);
		ActiveSkillAuto(_Time);
		Move(_Time,_Terrain,_MaxWidth,_MaxHeight);
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}


}
void SnakeMans::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if(ManagerObject::Instance()->getObjectCamera()->at(0)->getX()>=m_X+300)
	{
		m_Direct=1;
		m_X+=_Time* m_VMove;
	}
	if(ManagerObject::Instance()->getObjectCamera()->at(0)->getX()<=m_X-300)
	{
		m_Direct=-1;
		m_X-=_Time* m_VMove;
	}
	if(ManagerObject::Instance()->getObjectCamera()->at(0)->getX()<=m_X
		&&ManagerObject::Instance()->getObjectCamera()->at(0)->getX()+ManagerObject::Instance()->getObjectCamera()->at(0)->getWidth()>=m_X)
	{
		m_Direct=ManagerObject::Instance()->getObjectCamera()->at(0)->getDirection();
	}
}
void SnakeMans::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0)
	{
		m_InfoSprite.setScaleX(1);
	}
	else
	{
		m_InfoSprite.setScaleX(-1);
	}

	if(m_skillManager->getSkill(0)->getSTT()==ACTIVE||
		m_skillManager->getSkill(1)->getSTT()==ACTIVE||
		m_skillManager->getSkill(2)->getSTT()==ACTIVE||
		m_skillManager->getSkill(3)->getSTT()==ACTIVE)
	{

		for(int i=0;i<m_skillManager->getList().size();i++)
			if(m_skillManager->getSkill(i)->getSTT()==ACTIVE)
			{
				m_skillManager->getSkill(i)->Draw(_MWorld,_Handler);

			}
	}
	else
	{
		m_InfoSprite.setXY(m_X,m_Y);
		m_SCharater->Draw(_MWorld,m_InfoSprite,_Handler);
	}

}