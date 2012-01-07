#include "Magician.h"
#include "RSMainGame.h"
#include "Global.h"
#include "SkillMagician.h"

Magician::Magician(void)
{
	m_HP = 20000; 
	Init();

}


Magician::~Magician(void)
{
}

void Magician ::Init()
{
	m_SCharater= RSMainGame ::get()->getMagician();
	m_InfoSprite.setSize(300,200);
	m_STT = ACTIVE ;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new SkillMagician());
	setSize(50,85);
}

void Magician::Animation(float _Time){//1 walk,  2 jump, 3 alert, 4 hit, 5 skill
	m_TimeAni += _Time ;

	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
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
		break;
	}
}