#pragma once
#include "effectsystem.h"
#include "Character.h"
class EffectDiePrivate :
	public EffectSystem
{
public:
	Character *m_Character ;
	EffectDiePrivate(Character *_Character,float x, float y);
	~EffectDiePrivate(void);
	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

