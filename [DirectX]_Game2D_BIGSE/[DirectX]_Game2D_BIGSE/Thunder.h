#pragma once
#include "skill.h"
#include "MyObject.h"
class Thunder :
	public Skill
{
protected:
	MyObject *m_Character;
	Sprite *m_Thunder1;
	Sprite *m_Thunder2;
	InfoSprite m_InfoThunder1;
	InfoSprite m_InfoThunder2;
public:
	int t_STT ;
    virtual void Init () ;
	virtual void Active (float _X,float _Y,int _Dir);
	virtual void Animation (float _Time) ;
	/* Update status */
	virtual void UpdateStatus (float _Time) ;
	virtual void ProcessCollision(MyObject* _Obj);
	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;
	/* Draw Object */
	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);

	Thunder(void);
    Thunder(MyObject *_Character);
	~Thunder(void);
};

