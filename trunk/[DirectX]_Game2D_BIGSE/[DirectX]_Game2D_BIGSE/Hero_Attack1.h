#pragma once
#include "skill.h"
#include "Hero.h"
class Hero_Attack1 :
	public Skill
{
public:
	Hero* m_Hero;
	Sprite* m_Hero_Attack1Sprite;
	Sprite* m_Hero_Attack1_BallSprite;
	InfoSprite m_Hero_Attack1InfoSprite;
	InfoSprite m_Hero_Attack1_BallInfoSprite;

	bool Test1;

	int V;
	Hero_Attack1(Hero* _Hero);
	~Hero_Attack1(void);

	/* Active skill */
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

	/* Release */
/*	virtual void Release () ;*/
};

