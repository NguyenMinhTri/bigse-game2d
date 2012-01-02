#pragma once
#include "effectsystem.h"
class EffectFont :
	public EffectSystem
{
public:
	EffectFont(float _X, float _Y,int _Damage);
	virtual void Init();

	virtual void Update (float _Time);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	~EffectFont(void);
};

