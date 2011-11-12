#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include "Camera.h"
class State_Play :
	public iState
{
	Character* m_char;
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

