#pragma once
#include "character.h"
#include "myobject.h"
#include "Skill.h"
#include "SkillManager.h"

class Archer :

	public Character
{
protected:
	Sprite *m_Archer;
	bool arrow;
	bool COOLDOWN;
public:
	Archer(void);
	~Archer(void);
	
	virtual void Init () ;
	/* Processing collision */
	virtual void ProcessCollision (MyObject* _Obj);

	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) ;

	/* Update Move and check Collision with Terrain */
	

	/* Update Animation */
	virtual void Animation (float _Time) ;

	/* Update Status */
	virtual void UpdateStatus (float _Time) ;

	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;

	/* Release */
	virtual void Release () ;

	virtual void ActiveSkill (int _Index);

	/* Set move LEFT or RIGHT
	-1 LEFT
	 1 RIGHT
	*/
	void setMove (int _move);

	/* Set Jump */
	void setJump ();
};

