#pragma once
#include "effectsystem.h"
class ElephantDie :
	public EffectSystem
{
public:
	ElephantDie(float x, float y);
	~ElephantDie(void);
	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

