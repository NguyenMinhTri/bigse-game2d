#pragma once
#include "EffectSystem.h"
class EffectLaze :
	public EffectSystem
{
public:
	EffectLaze(void);
    EffectLaze(float x, float y);
	~EffectLaze(void);

	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

