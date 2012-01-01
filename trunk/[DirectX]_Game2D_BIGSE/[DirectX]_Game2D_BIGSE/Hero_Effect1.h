#pragma once
#include "effectsystem.h"
class Hero_Effect1 :
	public EffectSystem
{
public:



	Hero_Effect1(float _X, float _Y);
	~Hero_Effect1(void);
	virtual void Init();
	virtual void Animation(float _Time);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Update (float _Time);
};

