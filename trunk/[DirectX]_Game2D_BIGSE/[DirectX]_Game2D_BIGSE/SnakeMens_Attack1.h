#pragma once
#include "skill.h"
#include "SnakeMans.h"
class SnakeMens_Attack1 :
	public Skill
{
public:
	SnakeMans* m_SnakeMens;
	Sprite* m_SnakeMens_Attack1Sprite;
	InfoSprite m_SnakeMens_Attack1InfoSprite;

	SnakeMens_Attack1(SnakeMans* _SnakeMens);
	~SnakeMens_Attack1(void);

	virtual void Active (float _X,float _Y,int _Dir);

	virtual void Init () ;

	virtual void ProcessCollision(MyObject *_Obj);

	/* Update Animation */
	virtual void Animation (float _Time) ;

	/* Update status */
	virtual void UpdateStatus (float _Time) ;

	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
};

