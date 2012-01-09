#pragma once
#include "item.h"
class ItemSkull :
	public MyObject
{
public:
	Sprite* m_Item;
	int m_effect;
	float m_timeLife;
	ItemSkull(float x,float y) ;
	ItemSkull(void);
	virtual ~ItemSkull(void);

	virtual void Init();
	virtual void ProcessCollision (MyObject* _Obj) ;
	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) ;
	virtual void Animation (float _Time);
	virtual void UpdateStatus (float _Time) ;
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release () ;
	
};

