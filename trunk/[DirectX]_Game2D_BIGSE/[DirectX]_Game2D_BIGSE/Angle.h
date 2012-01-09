#pragma once
#include "character.h"
#include "SkillManager.h"

class Angle :
	public Character
{
public:
	int a ;
	float m_TimePrivate ;
	int count ;
	Angle(void);
	~Angle(void);
	virtual void Init () ;
	virtual void ActiveSkill(int _Index);
	virtual void Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Animation (float _Time) ;
	virtual void UpdateStatus(float _Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
};

