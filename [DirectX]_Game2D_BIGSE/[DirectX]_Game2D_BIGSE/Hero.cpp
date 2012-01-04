#include "Hero.h"
#include "Arrow.h"
#include "Hero_Attack1.h"
#include "Hero_Attack2.h"
#include "Hero_Attack3.h"
#include "Hero_Attack4.h"
#include "Hero_Die.h"
#include "ManagerObject.h"
Hero::Hero(void)
{
	Init();
}


Hero::~Hero(void)
{

}

void Hero::Init()
{
	m_SpriteHero_Move=RSMainGame::get()->getHero_Move();
	m_InfoSpriteHero_Move.setSize(79,103);

	m_SpriteHero_Stand=RSMainGame::get()->getHero_Stand();
	m_InfoSpriteHero_Stand.setSize(79,98);

	m_Hero_Die=RSMainGame::get()->getHero_Die();
	m_InfoHero_Die.setSize(212,202);



	setSize(79,90);
	m_STT=ACTIVE;
	m_HP=50;
	m_skillManager = new SkillManager();
	
	m_skillManager->AddSkill(new Hero_Attack4(this));
	m_skillManager->AddSkill(new Hero_Attack3(this));
	m_skillManager->AddSkill(new Hero_Attack1(this));
	m_skillManager->AddSkill(new Hero_Attack2(this));
}

void Hero::Animation(float _Time)
{
	m_TimeAni += _Time ;

	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			
			{
				if (m_Vy != 0 )
				{
					m_InfoSpriteHero=m_InfoSpriteHero_Move;
					m_SpriteHero=m_SpriteHero_Move;
				}
				else
				{
					if (m_VxDirect == 0)
					{
						m_InfoSpriteHero_Stand.NextFrame(0,4);
						if(m_InfoSpriteHero_Stand.getCurFrame() >3)
						{
							m_InfoSpriteHero_Stand.setCurFrame(0);
						}
						m_InfoSpriteHero=m_InfoSpriteHero_Stand;
						m_SpriteHero=m_SpriteHero_Stand;
					} 
					else
					{
						m_InfoSpriteHero_Move.NextFrame(0,3);
						if(m_InfoSpriteHero_Move.getCurFrame() >2)
						{
							m_InfoSpriteHero_Move.setCurFrame(0);
						}
						m_InfoSpriteHero=m_InfoSpriteHero_Move;
						m_SpriteHero=m_SpriteHero_Move;
					}

				}
			}
		}

		break;
	}
}

void Hero::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if(getLife()==false)
	{
		if (m_Direct<0)
		{
			Hero_Die *m_HeroDie = new Hero_Die(m_X-50,m_Y-50);
			m_HeroDie->m_InfoSprite.setScaleX(1);

			ManagerObject::Instance()->getListEffect()->push_back(m_HeroDie);
		}
		else
		{
			Hero_Die *m_HeroDie = new Hero_Die(m_X-100,m_Y-50);
			m_HeroDie->m_InfoSprite.setScaleX(-1);

			ManagerObject::Instance()->getListEffect()->push_back(m_HeroDie);
		}
	}
	else
	if(m_skillManager->getSkill(0)->getSTT()==ACTIVE||m_skillManager->getSkill(1)->getSTT()==ACTIVE||m_skillManager->getSkill(2)->getSTT()==ACTIVE||m_skillManager->getSkill(3)->getSTT()==ACTIVE)
	{
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
	else
	{
		UpdateStatus(_Time);
		Animation(_Time);
		Move(_Time,_Terrain,_MaxWidth,_MaxHeight);
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}


}

void Hero::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0)
	{
		m_InfoSpriteHero.setScaleX(1);
	}
	else
	{
		m_InfoSpriteHero.setScaleX(-1);
	}

	if(getLife()==false)
	{
		m_InfoHero_Die.setXY(m_X,m_Y);
		m_Hero_Die->Draw(_MWorld,m_InfoSpriteHero,_Handler);
	}
	else
	if(m_skillManager->getSkill(0)->getSTT()==ACTIVE||m_skillManager->getSkill(1)->getSTT()==ACTIVE||m_skillManager->getSkill(2)->getSTT()==ACTIVE||m_skillManager->getSkill(3)->getSTT()==ACTIVE)
	{

		for(int i=0;i<m_skillManager->getList().size();i++)
			if(m_skillManager->getSkill(i)->getSTT()==ACTIVE)
			{
				m_skillManager->getSkill(i)->Draw(_MWorld,_Handler);

			}
			
	}
	else
	{
		m_InfoSpriteHero.setXY(m_X,m_Y-3);
		m_SpriteHero->Draw(_MWorld,m_InfoSpriteHero,_Handler);
	}

}