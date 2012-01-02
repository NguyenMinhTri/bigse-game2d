#pragma once
#include "skill.h"
#include "Hero.h"
#include <vector>
using namespace std;
/*#include "Hero_Effect1.h"*/
class Hero_Attack4 :
	public Skill
{
public:
	Hero* m_Hero;
	int m_CountBall;
	Sprite* m_Hero_Attack4Sprite;
	InfoSprite m_Hero_Attack4InfoSprite;

	std::vector<Sprite*> *m_ListHero_Attack4_BallSprite;
	std::vector<InfoSprite> *m_ListHero_Attack4_BallInfoSprite;

	bool m_TestBallFly;
	int m_VBallFly;
	Hero_Attack4(Hero* _Hero);
	~Hero_Attack4(void);

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

