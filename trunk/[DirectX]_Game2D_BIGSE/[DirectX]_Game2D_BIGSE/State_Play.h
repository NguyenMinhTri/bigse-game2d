#pragma once
#include "istate.h"
#include "Character.h"
class State_Play :
	public iState
{
	Character* m_char;
	LPD3DXSPRITE m_Handle;
	int** m_Terrain;
public:
	State_Play(iPlay* GamePlay);
	~State_Play(void);
	void IsKeyDown(int KeyCode);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
};

