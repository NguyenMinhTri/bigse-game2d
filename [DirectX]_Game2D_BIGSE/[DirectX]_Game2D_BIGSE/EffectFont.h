#pragma once
#include "effectsystem.h"
class EffectFont :
	public EffectSystem
{
public:
	EffectFont(float _X, float _Y,int _Damage);
	void SetDamage (int _Damage)
	{
		m_Damage = _Damage;
	}
	virtual void Init();

	virtual void Update (float _Time);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Draw (LPD3DXSPRITE _Handler);
	~EffectFont(void);
};

