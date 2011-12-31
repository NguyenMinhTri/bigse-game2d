#include "SnakeMans.h"


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
	setSize(202,269);
	m_STT = ACTIVE ;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new Arrow());
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
