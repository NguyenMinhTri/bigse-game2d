#pragma once
#include "character.h"
#include "myobject.h"
#include "Skill.h"
#include "SkillManager.h"

class Archer :

	public Character
{
protected:
public:
	Archer(void);
	~Archer(void);

	virtual void Init () ;
	virtual void Animation (float _Time) ;


};
