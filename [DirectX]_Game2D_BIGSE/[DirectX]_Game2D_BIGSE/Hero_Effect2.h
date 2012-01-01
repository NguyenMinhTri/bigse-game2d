#pragma once
#include "effectsystem.h"
class Hero_Effect2 :
	public EffectSystem
{
public:
	Hero_Effect2(float _X, float _Y);
	~Hero_Effect2(void);
	virtual void Init();
	virtual void Animation(float _Time);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Update (float _Time);
};

