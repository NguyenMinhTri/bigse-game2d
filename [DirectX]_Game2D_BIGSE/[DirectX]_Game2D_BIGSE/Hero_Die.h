#pragma once
#include "effectsystem.h"
class Hero_Die :
	public EffectSystem
{
public:
	Hero_Die(float _X, float _Y);
	~Hero_Die(void);

	virtual void Init();
	virtual void Animation(float _Time);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Update (float _Time);
};

