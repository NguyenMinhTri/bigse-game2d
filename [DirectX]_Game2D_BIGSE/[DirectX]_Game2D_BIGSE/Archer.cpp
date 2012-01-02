#include "Archer.h"
#include "Character.h"
#include "RSMainGame.h"
#include "Global.h"
#include "Frenzy.h"
#include "CallPet.h"
#include "SkillArcher.h"
#include "Arrow.h"

Archer::Archer(void)
{
	Init();
	m_HP = 20000; 
}

Archer::~Archer(void)
{
}

void Archer ::Init()
{
	m_SCharater= RSMainGame ::get()->getArcher();
	m_InfoSprite.setSize(300,200);
	m_STT = ACTIVE ;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new SkillArcher());
	m_skillManager->AddSkill(new Arrow());
	
}

void Archer::Animation(float _Time){//1 walk,  2 jump, 3 alert, 4 hit, 5 skill
	m_TimeAni += _Time ;

	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			
			if(m_skillManager->getSkill(1)->getShoot() == true && m_skillManager->getSkill(1)->getSTT() ==ACTIVE)
			{
				m_InfoSprite.NextFrame(16,3);
			}
			else
			{
				if (m_Vy != 0 )
				{
					m_InfoSprite.NextFrame(4,3);
					if(m_InfoSprite.getCurFrame() >6)
					{
						m_InfoSprite.setCurFrame(4);
					}
				}
				else{
					if (m_VxDirect == 0){
						m_InfoSprite.NextFrame(8,4);
					} 
					else{
						m_InfoSprite.NextFrame(0,4);
					}
				}
			}				
		}
		break;
	}
}

