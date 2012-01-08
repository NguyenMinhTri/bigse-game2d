#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include <vector>
#include "InfoSprite.h"
#include "Effect_Setting.h"
using namespace std ;
class StateSetting:
	public iState
{
public:
	Sprite* m_Setting;
	InfoSprite m_InfoSetting;

	Sprite* m_Vector;
	InfoSprite m_InfoVector;

	Sprite* m_Button;
	InfoSprite m_InfoButton;
	Sprite* m_Tick;
	InfoSprite m_InfoTick;
	
	bool m_TestButton;
	bool m_TestClick;

	int m_CountOfEffect;
	float m_TimeToUpCount;
	vector<Effect_Setting*> *m_listEffect;
	bool test;

	float m_AniTime;
	D3DXMATRIX m_mtWorld;
	InfoSprite m_InfoSprite ;
	LPD3DXSPRITE m_Handle;
	StateSetting(iPlay* GamePlay);
	~StateSetting(void);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
	void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon) ;
};

