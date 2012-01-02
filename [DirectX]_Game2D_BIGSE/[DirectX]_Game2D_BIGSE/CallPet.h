#pragma once
#include "skill.h"
class CallPet :
	public Skill
{

public:
	CallPet(void);
	~CallPet(void);
	/* Active skill */
	virtual void Active (float _X,float _Y,int _Dir);

	virtual void Init () ;
	/* Update Animation */
	virtual void Animation (float _Time) ;

	/* Update status */
	virtual void UpdateStatus (float _Time) ;

	virtual void ProcessCollision(MyObject* _Obj);

	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);

	/* Release */
	virtual void Release () ;
};

