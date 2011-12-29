#pragma once
#include "myobject.h"
#include "Global.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Item.h"

#include "Character.h"

class Monster : public Character
{
protected:
	int count ;
	int m_Damage ;
	int m_Mana ;
	Sprite* m_Monster ;
	SkillManager *m_skillManager ; 

public:
	Monster(void);
	~Monster(void);
	virtual void Init () ;
	/* Processing collision */
	virtual void ProcessCollision (MyObject* _Obj);

	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) ;

	/* Update Move and check Collision with Terrain */
	void Move (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);

	/* Update Animation */
	void Animation (float _Time) ;

	/* Update Status */
	virtual void UpdateStatus (float _Time) ;

	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;
	/* Release */
	virtual void Release () ;
    virtual void ActiveSkill (int _Index);
};

