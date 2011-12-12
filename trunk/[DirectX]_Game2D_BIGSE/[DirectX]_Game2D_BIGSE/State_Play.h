#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include "Camera.h"
#include "Monster.h"
#include "Archer.h"
#include "Magician.h"

class State_Play :
	public iState
{
	Character* m_Monster ;
	Character* m_char;
    Archer *m_Archer; 

	Monster* m_Monster1;
	Magician* m_Magician;

	LPD3DXSPRITE m_Handle;
	Terrain* m_Map;
	Camera* m_Camera;
	D3DXMATRIX m_mtWorld;
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

