#pragma once
#include "skill.h"
#include "Character.h"
class Pharaon :
	public Skill
{
public:

	Sprite *m_Pharaon ;
	InfoSprite m_InfoSprite ;
	Character *m_Character ;
	Pharaon(Character *_Character);
	~Pharaon(void);
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
	virtual void Release () ;
};

