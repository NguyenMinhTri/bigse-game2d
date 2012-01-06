#pragma once
#include "myobject.h"
class GateSpace :
	public MyObject
{
public:
	int m_Direct ;
	Sprite* m_SpaceGate;
	InfoSprite m_InfoSprite ;

	virtual void Init();
	virtual void Animation(float _Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void UpdateStatus(float _Time);
	virtual void ProcessCollision(MyObject* _Obj);
	virtual bool iCollision(MyObject* _Obj);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;
	virtual void Release() ;

	GateSpace(int _Direction);
	~GateSpace(void);
};

