#pragma once

#include "istate.h"
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include <vector>
#include "InfoSprite.h"

using namespace std ;
class StatePlayer :
	public iState
{
public:

	Sprite* m_BackGround;
	InfoSprite m_InfoBG;
	Sprite* m_SwordMan ;
	InfoSprite m_InfoSword ;

	Sprite* m_Magician ;
	InfoSprite m_InfoMagician ;
	
	Sprite* m_Punch ;
	InfoSprite m_InfoPunch ;

	Sprite* m_Flag;
	InfoSprite m_InfoFlag;
    LPD3DXSPRITE m_Handle;

	int g_STT ;
	int t_STT ;
	int z_STT ;
	float m_TimeAni ;

	StatePlayer(iPlay* GamePlay);
	~StatePlayer(void);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
	
	void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon) ;
	
};

