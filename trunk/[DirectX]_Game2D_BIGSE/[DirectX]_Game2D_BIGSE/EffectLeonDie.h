#pragma once
#include "EffectSystem.h"
#include "InfoSprite.h"
class EffectLeonDie : public EffectSystem
{
public:
	Sprite* m_VonLeon1;
	Sprite* m_VonLeon2;

	InfoSprite m_InfoSprite1;
	InfoSprite m_InfoSprite2;

	int e_STT ;

	EffectLeonDie(float x,float y);
	~EffectLeonDie(void);

	virtual void Init();
	virtual void Update(float _Time);
	virtual void Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release();
};

