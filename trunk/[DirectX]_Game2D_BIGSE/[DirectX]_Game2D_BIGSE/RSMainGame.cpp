#include "RSMainGame.h"
RSMainGame* RSMainGame::instance = NULL;

RSMainGame::RSMainGame(void)
{
}


RSMainGame::~RSMainGame(void)
{
}

void RSMainGame::IntRS(LPDIRECT3DDEVICE9 _Device){

	m_Character = new Sprite(_Device,
		"data\\image\\character.png",300,200,4);

	m_Terrain = new Sprite(_Device,
		"data\\image\\ter.png",50,70,1);
}
