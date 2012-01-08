#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include <vector>
#include "InfoSprite.h"
#include "Effect_Help.h"
using namespace std ;
class StateHelp:
	public iState
{
public:
	Sprite* m_Help;
	InfoSprite m_InfoHelp;

	Sprite* m_Vector;
	InfoSprite m_InfoVector;
	int m_CountOfEffect;
	float m_TimeToUpCount;
	vector<Effect_Help*> *m_listEffect;
	bool test;
	float m_AniTime;
	D3DXMATRIX m_mtWorld;
	InfoSprite m_InfoSprite ;
	LPD3DXSPRITE m_Handle;
	StateHelp(iPlay* GamePlay);
	~StateHelp(void);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
	void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon) ;
};

