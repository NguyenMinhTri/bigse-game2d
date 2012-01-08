#include "SkillAngle.h"
#include "RSMainGame.h"
#include "SoundGame.h"
SkillAngle::SkillAngle(Angle *_Angle)
{
	Init();
	m_Angle = _Angle;
}

void SkillAngle::Init(){
	m_Damage = 1;
	m_STT = READY;
	setSize(150,100);
	m_SSkill = RSMainGame::get()->getAngle();
}
SkillAngle::~SkillAngle(void)
{
}

void SkillAngle::Active (float _X,float _Y,int _Dir)
{	
	if(m_STT!=ACTIVE)
	{
		if (_Dir>0)
		{
			m_X = _X ;
			m_Y = _Y;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X + 50 - m_Width ;
			m_Y = _Y;
			m_Direct = _Dir;
		}

		m_InfoSprite.setCurFrame(12);
		m_TimeAni = 0;	
		m_STT = ACTIVE;
		m_iCollision = true;
	}
}
void SkillAngle ::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		SoundGame ::Instance()->PlayAngleXetXet();
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;

			m_InfoSprite.NextFrame(12,5);
			if (m_InfoSprite.getCurFrame() ==16 )
			{				
				m_STT = READY;
				m_TimeAni =0;
			}
		}
	}
}

