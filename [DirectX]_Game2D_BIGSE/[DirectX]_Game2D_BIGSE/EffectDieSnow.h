#pragma once
#include "effectsystem.h"
class EffectDieSnow :
	public EffectSystem
{
public:
	EffectDieSnow(float x, float y);
	~EffectDieSnow(void);
	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

