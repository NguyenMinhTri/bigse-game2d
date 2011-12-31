#pragma once
#include "Effectsystem.h"
class EffectThunder :
	public EffectSystem
{
public:
    EffectThunder(float x, float y);
	~EffectThunder(void);

	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

