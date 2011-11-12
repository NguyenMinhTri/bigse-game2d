#pragma once
#include "MyObject.h"
class Skill : public MyObject
{
protected:
	int m_Combo;
	bool m_NextCombo;
	int m_Dir;
	Sprite* m_SSkill;
public:
	Skill(void);
	virtual ~Skill(void);

	/* Active skill */
	virtual void Active (float _X,float _Y,int _Dir);

	/* Get damage for collision 
	Random from Damage to Damage+Offset */
	virtual int getDamageEX (int _Damage, int _Offset){return 0;};

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
	virtual void Update (float _Time) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);

	/* Release */
	virtual void Release () ;
};

