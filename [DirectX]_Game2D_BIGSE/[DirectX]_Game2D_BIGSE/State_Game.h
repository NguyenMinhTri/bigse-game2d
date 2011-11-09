#pragma once
#include "istate.h"
#include "Sprite.h"


class MainGame :
	public iState
{
private:	
	float m_Ro;
	float m_ScaleX,m_ScaleY;
	Sprite* m_sMario;
	InfoSprite m_infoSprite;
	LPD3DXSPRITE m_Handle;

public:
	MainGame(iPlay* GamePlay);
	~MainGame(void);
	void IsKeyDown(int KeyCode);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
};

