#pragma once
#include "skill.h"
#include "GodLike_Beast.h"
class GodLike_Attack4 :
	public Skill
{
public:
	int m_Damage ;
	int count;
	GodLike_Beast *m_GodLike ;
	Sprite *m_Attack4_1;
	Sprite *m_Attack4_2;
	Sprite *m_Attack4;

	InfoSprite m_InfoSprite4_1;
	InfoSprite m_InfoSprite4_2;
	InfoSprite m_InfoSprite4 ;

	int t_STT ;

	GodLike_Attack4(GodLike_Beast* _GodLike);
	~GodLike_Attack4(void);

	virtual void Init();
	virtual void Active (float _X,float _Y,int _Dir);

	virtual void ProcessCollision(MyObject *_Obj);

	/* Update Animation */
	virtual void Animation (float _Time) ;

	/* Update status */
	virtual void UpdateStatus (float _Time) ;

	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
};

