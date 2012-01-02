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
	m_GodLikeAttack3 = new Sprite(_Device,"data\\image\\GodLike_Attack3.png",717,603,4);
	m_GodLikeAttack4_1 = new Sprite(_Device,"data\\image\\GodLike_Attack4_1.png",1346,639,3);
	m_GodLikeAttack4_2 = new Sprite(_Device,"data\\image\\GodLike_Attack4 _2.png",1346,639,3);
	m_EffectLaze = new Sprite(_Device,"data\\image\\EffectLaze.png",103,106,7);
	m_EffectSound = new Sprite(_Device,"data\\image\\EffectSound.png",151,151,4);
	m_EffectThunder = new Sprite(_Device,"data\\image\\EffectThunder.png",182,129,5);
	m_EffectHit = new Sprite(_Device,"data\\image\\EffectHit.png",197,177,6);
	m_EffectLeonDie_1 = new Sprite(_Device,"data\\image\\GodLike_dIE.png",732,700,4);
	m_EffectLeonDie_2 = new Sprite(_Device,"data\\image\\GodLike_dIE_2.png",732,700,4);
	m_Teleport = new Sprite(_Device,"data\\image\\TelePort.png",568,574,4);
	m_Teleport1 = new Sprite(_Device,"data\\image\\TelePort1.png",568,574,4);
	
	m_FontNum = new Sprite(_Device,"data\\image\\num.png",37,39,10 );

	m_SnakeMans_Move = new Sprite(_Device,"data\\image\\SnakeMans_Move.png",202,269,6);
	m_Hero_Move=new Sprite(_Device,"data\\image\\Hero_Move.png",79,103,6);
	m_Hero_Stand=new Sprite(_Device,"data\\image\\Hero_Stand.png",79,98,4);
	m_Hero_Attack1=new Sprite(_Device,"data\\image\\Hero_Attack1.png",570,255,4);
	m_Hero_Attack1_Ball=new Sprite(_Device,"data\\image\\Hero_Attack1_Ball.png",415,143,5);
	m_Hero_Effect1=new Sprite(_Device,"data\\image\\Hero_Attack1_Hit.png",96,113,6);
	m_Hero_Attack2=new Sprite(_Device,"data\\image\\Hero_Attack2.png",294,164,5);
	m_Hero_Attack3=new Sprite(_Device,"data\\image\\Hero_Attack3.png",274,231,5);
	m_Hero_Attack3_Ball=new Sprite(_Device,"data\\image\\Hero_Attack3_Ball.png",97,150,7);
	m_Hero_Effect2=new Sprite(_Device,"data\\image\\Hero_Attack3_Hit.png",124,109,5);

}
