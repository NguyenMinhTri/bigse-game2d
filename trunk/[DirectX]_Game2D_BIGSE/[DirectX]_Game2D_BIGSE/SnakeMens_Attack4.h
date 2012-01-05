#pragma once
#include "skill.h"
#include "SnakeMans.h"
class SnakeMens_Attack4 :
	public Skill
{
public:
	SnakeMans* m_SnakeMens;
	Sprite* m_SnakeMens_Attack4Sprite;
	Sprite* m_SnakeMens_Attack4_BallSprite;
	InfoSprite m_SnakeMens_Attack4InfoSprite;
	InfoSprite m_SnakeMens_Attack4_BallInfoSprite;
	bool m_TestBallFly;
	int m_VBallFly;
	SnakeMens_Attack4(SnakeMans* _SnakeMens);
	~SnakeMens_Attack4(void);

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

