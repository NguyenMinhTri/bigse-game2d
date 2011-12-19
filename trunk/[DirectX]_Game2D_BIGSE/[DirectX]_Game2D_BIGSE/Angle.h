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
	virtual void Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Animation (float _Time) ;
};

