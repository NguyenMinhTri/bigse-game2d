#include "Angle.h"
#include "RSMainGame.h"
#include "SkillAngle.h"
#include "Thunder.h"
Angle::Angle(void)
{
	Init();
	m_HP = 2;
}


Angle::~Angle(void)
{
}
void Angle ::Init()
{
	m_SCharater= RSMainGame ::get()->getAngle();
	m_InfoSprite.setSize(300,200);
	setSize(50,85);
	setXY(200,0);
	m_STT = ACTIVE ;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new SkillAngle(this));
    m_skillManager->AddSkill(new Thunder(this));
}
void Angle ::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if(m_skillManager->getSkill(1)->time !=TIME)
	MyObject::Move(_Time, _Terrain,_MaxWidth,_MaxHeight);
}
void Angle ::Animation(float _Time)
{
	m_TimeAni +=_Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			if(m_skillManager->getSkill(1)->time ==TIME)
			{
				m_InfoSprite.setCurFrame(4);
				setY(getY() - 5);
			}
			if (m_Vy != 0  && m_skillManager->getSkill(1)->time !=TIME)
			{
				m_InfoSprite.NextFrame(4,3);
				if(m_InfoSprite.getCurFrame() >6)
				{
					m_InfoSprite.setCurFrame(4);
				}
			}
			else
			{
				if (m_VxDirect == 0  && m_skillManager->getSkill(1)->time !=TIME)
				{
					m_InfoSprite.NextFrame(8,4);
				} 
				else if(m_VxDirect !=0  && m_skillManager->getSkill(1)->time !=TIME)
				{
					m_InfoSprite.NextFrame(0,4);
				}
			}
		}
		break;
	}
}