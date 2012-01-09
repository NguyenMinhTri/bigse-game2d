#pragma once
#include "Skill.h"

#include "Angle.h"
#include "SkillHit.h"
class SkillAngle :
	public SkillHit
{
protected:
	Angle *m_Angle ;
public:
	SkillAngle(Angle *_Angle);
	~SkillAngle(void);
	virtual void Init () ;
	virtual void Active (float _X,float _Y,int _Dir);
	virtual void Animation (float _Time) ;
};

