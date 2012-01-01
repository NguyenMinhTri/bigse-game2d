#pragma once
#include "skill.h"
#include "Hero.h"
#include "Hero_Effect1.h"
class Hero_Attack2 :
	public Skill
{
public:
	Hero* m_Hero;
	Sprite* m_Hero_Attack2Sprite;
	InfoSprite m_Hero_Attack2InfoSprite;

	Hero_Attack2(Hero* _Hero);
	~Hero_Attack2(void);

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

