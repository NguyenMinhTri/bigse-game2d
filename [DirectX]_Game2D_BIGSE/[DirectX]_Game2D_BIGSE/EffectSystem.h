#pragma once
#include "Global.h"
#include <list>
#include "InfoSprite.h"
#include "RECT.h"
#include "Sprite.h"
using namespace std ;
class EffectSystem 
{
public:
	Sprite* m_Sprite ;
	/* All information sprite for render*/
	InfoSprite m_InfoSprite;
	int m_ID;

	int m_HP;
	int m_Damage;

	int m_Direct;

	/* Status */
	int m_STT,m_OldSTT;

	/* Position */
	float m_X,m_Y;

	/* Velocity */
	float m_Vx, m_Vy;

	/* Gravity */
	float m_Gravity;

	/* Direct move X */
	float m_VxDirect;

	/* Size */
	float m_Width,m_Height;

	/* Time for Update */
	float m_TimeUpdate;

	/* Time for Animation */
	float m_TimeAni;
	/*Sprite m_Sprite;*/
	bool m_iFrenzy;
	bool m_iFire;
	bool m_iLife;
	bool m_iActive ;

	EffectSystem(float _X, float _Y);
	EffectSystem(void);
	virtual ~EffectSystem(void);

	virtual void Init();
	virtual void Animation (float _Time);
	virtual void UpdateStatus (float _Time) ;
	virtual void Update (float _Time);

	virtual void Draw (D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
	virtual void Release () ;
};
