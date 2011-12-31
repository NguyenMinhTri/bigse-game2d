#pragma once
#include "EffectSystem.h"

class EffectSound : public EffectSystem
{
public:
	EffectSound(float x, float y);
	~EffectSound(void);

	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

