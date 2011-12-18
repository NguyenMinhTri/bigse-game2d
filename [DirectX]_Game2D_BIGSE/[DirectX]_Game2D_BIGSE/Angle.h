#pragma once
#include "character.h"
#include "SkillManager.h"
class Angle :
	public Character
{
public:
	Angle(void);
	~Angle(void);
	virtual void Init () ;
	virtual void Animation (float _Time) ;
};

