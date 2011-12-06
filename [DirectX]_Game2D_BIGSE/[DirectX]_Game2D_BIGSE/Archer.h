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
	

	/* Update Move and check Collision with Terrain */
	

	/* Update Animation */
	virtual void Animation (float _Time) ;



	/* Draw Object */
	virtual void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;

	/* Release */
	virtual void Release () ;

	virtual void ActiveSkill (int _Index);

	/* Set Jump */
	void setJump ();
};

