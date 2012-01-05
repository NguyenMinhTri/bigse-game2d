#pragma once
#include "effectsystem.h"
class EffectInfoEle :
	public EffectSystem
{
public:
	EffectInfoEle(float x, float y);
	~EffectInfoEle(void);
	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

