#pragma once
#include "monster.h"
class Trap :
	public MyObject
{
public:
	Sprite* m_Trap ;
	InfoSprite m_InfoTrap ;
	virtual void Init() ;

	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void UpdateStatus(float _Time);
	virtual void Animation(float _Time);
	virtual void ProcessCollision(MyObject* _Obj);
	virtual bool iCollision(MyObject* _Obj);

	virtual void Release() ;

	Trap(void);
	~Trap(void);
};

