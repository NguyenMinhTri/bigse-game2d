#pragma once
#include "skill.h"
#include "Hero.h"
class Hero_Attack3 :
	public Skill
{
public:
	Hero* m_Hero;
	Sprite* m_Hero_Attack3Sprite;
	Sprite* m_Hero_Attack3_BallSprite;
	InfoSprite m_Hero_Attack3InfoSprite;
	InfoSprite m_Hero_Attack3_BallInfoSprite;
	bool m_TestBallFly;
	int m_VBallFly;

	Hero_Attack3(Hero* _Hero);
	~Hero_Attack3(void);

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

};

