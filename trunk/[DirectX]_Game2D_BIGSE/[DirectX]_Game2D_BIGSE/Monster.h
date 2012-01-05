#pragma once
#include "myobject.h"
#include "Global.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Item.h"
#include "ElephantAttack.h"
#include "Character.h"

class Monster : public Character //Elephant 
{
protected:
	int m_Damage ;
	float m_TimePrivate ;
	int v_x ;
	Sprite* m_ElephantMove ;
	InfoSprite m_InfoMove ;
	SkillManager *m_skillManager ; 

public:
	bool m_Hit ;
	Monster(void);
	~Monster(void);
	virtual void Init () ;
	/* Processing collision */
	virtual void ProcessCollision (MyObject* _Obj);

	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) ;
	virtual void setJump() ;

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

