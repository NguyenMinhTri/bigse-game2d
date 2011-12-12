#pragma once
#include <list>
#include "MyObject.h"
using namespace std;
class Skill : public MyObject
{
protected:
	int m_Combo;
	bool m_NextCombo;

	Sprite* m_SSkill;
	bool timeshoot;
	bool m_iCollision;

public:
	Skill(void);
	virtual ~Skill(void);

	bool getShoot()
	{
		return timeshoot;
	}
	void setShoot(bool q)
	{
		timeshoot = q;
	}

	/* Active skill */
	virtual void Active (float _X,float _Y,int _Dir);

	/* Get damage for collision 
	Random from Damage to Damage+Offset */
	virtual int getDamageEX (int _Damage, int _Offset);

	virtual void Init () ;
	/* Processing collision */
	virtual void ProcessCollision (MyObject* _Obj) ;

	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) ;

	/* Update Move and check Collision with Terrain */
	virtual void Move (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Update Animation */
	virtual void Animation (float _Time) ;

	/* Update status */
	virtual void UpdateStatus (float _Time) ;

	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);

	/* Release */
	virtual void Release () ;
};

