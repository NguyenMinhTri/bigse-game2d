#pragma once
#include "skill.h"
#include "GodLike_Beast.h"
class GodLike_Attack3 :
	public Skill
{
public:

	GodLike_Beast *m_GodLike ;
	Sprite *m_Attack1 ;
	InfoSprite m_InfoSprite1;

	GodLike_Attack3(GodLike_Beast *_GodLike);
	GodLike_Attack3(void);
	~GodLike_Attack3(void);

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
	virtual void Release() ;

};