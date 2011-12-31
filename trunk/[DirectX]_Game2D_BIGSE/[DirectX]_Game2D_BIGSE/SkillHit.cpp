#include "SkillHit.h"
#include "Global.h"
#include "EffectHit.h"
#include "ManagerObject.h"


SkillHit::SkillHit(Character* _Character)
{
	m_Character = _Character;
}


SkillHit::~SkillHit(void)
{
}

void SkillHit::Active (float _X,float _Y,int _Dir)
{
	if (m_STT != ACTIVE) //chua tung skill
	{
		if (_Dir>0)
		{
			m_X = _X;
			m_Y = _Y;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X + 50- m_Width ;
			m_Y = _Y;
			m_Direct = _Dir;
		}

		m_STT = ACTIVE;	

		m_TypeSkill = rand()%4;
		m_TimeAni = 0;
		m_iCollision = false;
		switch (m_TypeSkill)
		{
		case 0:
			m_InfoSprite.setCurFrame(12);
			break;
		case 1:
			m_InfoSprite.setCurFrame(16);
			break;
		case 2:
			m_InfoSprite.setCurFrame(20);
			break;
		case 3:
			m_InfoSprite.setCurFrame(24);
			break;
		}
	}
}
void SkillHit::Animation(float _Time)
{

	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			switch(m_TypeSkill)
			{
			case 0:
				m_InfoSprite.NextFrame(12,4);
				if (m_InfoSprite.getCurFrame()>=13)
				{				
					m_iCollision = true;									
				}
				if (m_InfoSprite.getCurFrame()>14)
				{				
					m_STT = READY;									
				}
				break;
			case 1:
				m_InfoSprite.NextFrame(16,4);
				if (m_InfoSprite.getCurFrame()>=17)
				{				
					m_iCollision = true;									
				}
				if (m_InfoSprite.getCurFrame()>18)
				{				
					m_STT = READY;								
				}
				break;
			case 2:
				m_InfoSprite.NextFrame(20,4);
				if (m_InfoSprite.getCurFrame()>=21)
				{				
					m_iCollision = true;									
				}
				if (m_InfoSprite.getCurFrame()>22)
				{
					m_STT = READY;
				}
				break;
			case 3:
				m_InfoSprite.NextFrame(24,5);
				if (m_InfoSprite.getCurFrame()>=25)
				{				
					m_iCollision = true;									
				}
				if (m_InfoSprite.getCurFrame()>27) 
				{
					m_STT = READY;	
				}
				break;
			}					
		}
	}
}

void SkillHit ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung


		EffectHit* m_Effecthit = new EffectHit(m_X,m_Y - 30);
		ManagerObject::Instance()->getListEffect()->push_back(m_Effecthit);

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - 1 );
		if(_Obj->getHp() == 0)
		{
			_Obj->setLife(false); 
		}	
	}
}

void SkillHit::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if (m_STT==ACTIVE)
	{
		m_Direct = m_Character->getDirection();
		if (m_Character->getDirection()>0)
		{
			m_X = m_Character->getX();
			m_Y = m_Character->getY();
			
		} 
		else
		{
			m_X = m_Character->getX() + 50- m_Width ;
			m_Y = m_Character->getY();			
		}
	}
	Animation(_Time);
}