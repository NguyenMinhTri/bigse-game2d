#pragma once
#include "EffectSystem.h"
class EffectFrenzy :
	public EffectSystem
{
public:
	bool m_Time ;
	EffectFrenzy(void);
	EffectFrenzy(float x,float y);
	~EffectFrenzy(void);
	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

