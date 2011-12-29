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
		"data\\image\\ice.png",435,419,2);
	m_Pet = new Sprite(_Device,"data\\image\\callPet.png",520,385,6 );
	m_Archer = new Sprite(_Device,"data\\image\\cungthu.png",300,200,4);
	m_Arrow = new Sprite(_Device,"data\\image\\Arrow.png",232,67,4);
	m_Magician = new Sprite(_Device,"data\\image\\Magician.png",300,200,4);
	m_medicine = new Sprite(_Device,"data\\image\\Medicine.png",52,63,1);
	m_Partner= new Sprite(_Device,"data\\image\\Dragon.png",100,80,6);
	m_Angle = new Sprite(_Device,"data\\image\\Angle.png",300,200,4);
	m_Thunder1 = new Sprite(_Device,"data\\image\\thunder.png",1199,598,3);
	m_Thunder2 = new Sprite(_Device,"data\\image\\thunder2.png",1199,598,3);
	m_EffectIce = new Sprite(_Device,"data\\image\\EffectIce.png",137,155,5);
	m_EffectDie = new Sprite(_Device,"data\\image\\Die.png",170,229,4);
	m_FrenzyTime = new Sprite(_Device,"data\\image\\DongBangThoiGian_image.png",38,38,1);
	m_GodLikeMove = new Sprite(_Device,"data\\image\\GodLike_Move.png",566,524,4);
	m_GodLikeStand = new Sprite(_Device,"data\\image\\GodLike_Stand.png",554,509,6);
	m_GodLikeAttack1 = new Sprite(_Device,"data\\image\\GodLike_Attack1.png",802,647,4);
	m_GodLikeAttack2 = new Sprite(_Device,"data\\image\\GodLike_Attack2.png",987,732,4);
}
