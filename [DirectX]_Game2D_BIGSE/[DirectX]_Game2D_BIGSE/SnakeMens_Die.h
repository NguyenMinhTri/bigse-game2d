#pragma once
#include "effectsystem.h"
class SnakeMens_Die :
	public EffectSystem
{
public:
	SnakeMens_Die(float _X, float _Y);
	~SnakeMens_Die(void);

	virtual void Init();
	virtual void Animation(float _Time);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Update (float _Time);
};

