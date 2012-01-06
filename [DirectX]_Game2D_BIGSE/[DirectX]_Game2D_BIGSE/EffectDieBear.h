#pragma once
#include "effectsystem.h"
#include "Character.h"
class EffectDieBear :
	public EffectSystem
{
public:
	Character *m_Character ;
	EffectDieBear(Character *_Character,float x, float y);
	~EffectDieBear(void);
	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

