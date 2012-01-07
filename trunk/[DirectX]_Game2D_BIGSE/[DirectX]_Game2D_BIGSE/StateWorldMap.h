#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include <vector>
#include "InfoSprite.h"
#include "RECT.h"

using namespace std ;
class StateWorldMap :
	public iState
{
public:
	CRECT r ;
	CRECT Perion ;
	CRECT Kerningstadt ;
	CRECT Kerningplatz ;
	CRECT LithHafen ;
	CRECT Henesys ;
	CRECT Nautilus ;
	CRECT Ellinia ;
	CRECT FloringStrand ;
	CRECT SechsWegeKreuzung ;

	float m_TimeAni ;
	int m_STT ;
	Sprite * m_Character ;
	Sprite *m_CharacterAttack;
	Sprite *m_WorldMap ;
	D3DXMATRIX m_mtWorld;
	InfoSprite m_InfoSprite ;
	InfoSprite m_InfoCharacter;
	InfoSprite m_InfoAttack ;
	LPD3DXSPRITE m_Handle;
	StateWorldMap(iPlay* GamePlay);
	~StateWorldMap(void);

	void IsKeyDown(int KeyCode);
 	void OnKeyDown(int KeyCode);
// 	void OnKeyUp(int KeyCode);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
	void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon) ;
};

