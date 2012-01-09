#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include <vector>
#include "InfoSprite.h"
#include "Effect_Setting.h"
using namespace std ;
class StateWin:
	public iState
{
public:
	Sprite* m_Win;
	InfoSprite m_InfoWin;

	Sprite* m_Vector;
	InfoSprite m_InfoVector;
	int m_CountOfEffect;
	float m_TimeToUpCount;
	vector<Effect_Setting*> *m_listEffect;
	bool test;
	float m_AniTime;
	D3DXMATRIX m_mtWorld;
	InfoSprite m_InfoSprite ;
	LPD3DXSPRITE m_Handle;
	StateWin(iPlay* GamePlay);
	~StateWin(void);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
	void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon) ;
};

