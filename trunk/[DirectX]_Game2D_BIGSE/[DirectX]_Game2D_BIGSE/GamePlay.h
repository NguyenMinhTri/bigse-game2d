#pragma once
#include "iPlay.h"
#include "State_Game.h"
class GamePlay:public iPlay
{
public:
	GamePlay(LPDIRECT3DDEVICE9 Device);
	~GamePlay(void);
	void Init ();
	void Update (float _Time);
	void Draw ();
	void Release ();
};

