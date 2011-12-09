#pragma once
#include "skill.h"

class SkillMagician :
	public Skill
{
public:
	SkillMagician(void);
	~SkillMagician(void);
	virtual void Active (float _X,float _Y,int _Dir);
	virtual void Init () ;
	/* Update Animation */
	virtual void Animation (float _Time) ;
	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	/* Release */
	virtual void Release () ;
};

