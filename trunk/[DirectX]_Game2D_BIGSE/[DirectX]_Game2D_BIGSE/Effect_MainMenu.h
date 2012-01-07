#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include <vector>
#include "InfoSprite.h"
using namespace std ;
class Effect_MainMenu
{
public:
	Sprite* m_Effect;
	InfoSprite m_InfoEffect;
	float m_timeLife;
	float m_Old;
	Effect_MainMenu(LPDIRECT3DDEVICE9 m_Device);
	~Effect_MainMenu(void);
};

