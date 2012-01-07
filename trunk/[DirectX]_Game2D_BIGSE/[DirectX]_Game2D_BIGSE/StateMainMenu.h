#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include <vector>
#include "InfoSprite.h"
#include "Effect_MainMenu.h"

using namespace std ;

class StateMainMenu :
	public iState
{
public:
	int m_DirectOfMain;
	float CoAlMain;
	float CoAlLogo;
	float m_AnTime;
	bool test;
	int m_CountOfEffect;
	float m_TimeToUpCount;
	vector<Effect_MainMenu*> *m_listEffect;


	Sprite *m_MainMenu ;
	InfoSprite m_InfoMainMenu ;

	Sprite *m_Bird1 ;
	InfoSprite m_InfoBird1;

	Sprite *m_Bird2 ;
	InfoSprite m_InfoBird2;

	Sprite *m_Logo ;
	InfoSprite m_InfoLogo ;

	Sprite *m_ButtonStart ;
	InfoSprite m_InfoButtonStart ;

	Sprite *m_ButtonSetting ;
	InfoSprite m_InfoButtonSetting ;

	Sprite *m_ButtonHelp ;
	InfoSprite m_InfoButtonHelp ;

	Sprite *m_ButtonExit ;
	InfoSprite m_InfoButtonExit ;
	
	vector<Sprite*> *m_listHoldButton;
	vector<InfoSprite> *m_listInfoHoldButton;

	D3DXMATRIX m_mtWorld;
	InfoSprite m_InfoSprite ;
	LPD3DXSPRITE m_Handle;
	StateMainMenu(iPlay* GamePlay);
	~StateMainMenu(void);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
	void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon) ;
};
