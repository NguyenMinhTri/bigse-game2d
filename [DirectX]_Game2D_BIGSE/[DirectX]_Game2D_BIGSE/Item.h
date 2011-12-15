#pragma once
#include "Myobject.h"
#include "Global.h"
using namespace std;
class Item :
	public MyObject
{
protected:
	
	Sprite* m_Item;
	int m_effect;
	float m_timeLife;

public:
	Item(float x, float y);
	Item(void);
	virtual ~Item(void);
	virtual void Init();
	virtual void ProcessCollision (MyObject* _Obj) ;

	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) ;
	virtual void Animation (float _Time);
	virtual void UpdateStatus (float _Time) ;
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release () ;
};

