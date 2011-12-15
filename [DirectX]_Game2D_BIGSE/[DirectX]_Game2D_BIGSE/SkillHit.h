#pragma once
#include "skill.h"
#include "Character.h"
class SkillHit :
	public Skill
{
private:
	Character *m_Character;
	int m_TypeSkill; // random 0-3
public:
	SkillHit(Character* _Character);
	~SkillHit(void);
	virtual void Active (float _X,float _Y,int _Dir);
	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;
	/* Update Animation */
	virtual void Animation (float _Time) ;
};

