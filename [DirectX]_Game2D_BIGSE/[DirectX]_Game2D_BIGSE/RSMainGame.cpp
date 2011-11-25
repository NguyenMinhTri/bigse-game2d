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

	m_Frenzy = new Sprite(_Device,
		"data\\image\\Frenzy.png",421,394,1);
	m_Pet = new Sprite(_Device,"data\\image\\callThu.png",283,189,21 );
	
}
