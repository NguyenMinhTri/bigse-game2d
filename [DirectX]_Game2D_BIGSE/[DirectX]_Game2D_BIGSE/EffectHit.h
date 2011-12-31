#pragma once
#include "EffectSystem.h"
class EffectHit :
	public EffectSystem
{
public:
	EffectHit(float x,float y);
	~EffectHit(void);
	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

