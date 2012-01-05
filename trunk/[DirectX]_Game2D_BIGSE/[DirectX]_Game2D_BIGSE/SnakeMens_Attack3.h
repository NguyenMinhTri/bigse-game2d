#pragma once
#include "skill.h"
#include "SnakeMans.h"
#include <vector>
using namespace std;
/*#include "Hero_Effect1.h"*/
class SnakeMens_Attack3 :
	public Skill
{
public:
	SnakeMans* m_SnakeMens;
	int m_CountBall;
	Sprite* m_SnakeMens_Attack3Sprite;
	InfoSprite m_SnakeMens_Attack3InfoSprite;

	std::vector<Sprite*> *m_ListSnakeMens_Attack3_BallSprite;
	std::vector<InfoSprite> *m_ListSnakeMens_Attack3_BallInfoSprite;

	bool m_TestBallFly;
	int m_VBallFly;
	SnakeMens_Attack3(SnakeMans* _SnakeMans);
	~SnakeMens_Attack3(void);

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

