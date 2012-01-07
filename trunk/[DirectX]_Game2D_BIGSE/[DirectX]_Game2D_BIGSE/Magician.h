#pragma once
#include "character.h"
class Magician :
	public Character
{
public:
	Magician(void);
	~Magician(void);
	virtual void Init () ;
	virtual void Animation (float _Time) ;
	/*virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);*/
};

