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
	m_IC = new Sprite(_Device,"data\\image\\IC.png",52,50,13 );
	m_IC2 = new Sprite(_Device,"data\\image\\IC2.png",50,80,2 );
	m_Grass = new Sprite(_Device,"data\\image\\TerGrass.png",52,50,13 );
	m_Grass2 = new Sprite(_Device,"data\\image\\TerGrass2.png",50,80,2 );
	m_FontNum = new Sprite(_Device,"data\\image\\num.png",37,39,10 );
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
	/////////////////////////////////////
	m_SnakeMans_Move = new Sprite(_Device,"data\\image\\SnakeMans_Move.png",202,269,6);
	m_SnakeMans_Die=new Sprite(_Device,"data\\image\\SnakeMans_Die.png",312,421,10);

	m_SnakeMans_attack1=new Sprite(_Device,"data\\image\\SnakeMans_attack1.png",721,280,5);
	m_SnakeMans_Attack1_Hit=new Sprite(_Device,"data\\image\\SnakeMans_Attack1_Hit.png",200,135,5);

	m_SnakeMans_attack2=new Sprite(_Device,"data\\image\\SnakeMans_attack2.png",523,385,5);
	m_SnakeMans_Attack2_info_ball=new Sprite(_Device,"data\\image\\SnakeMans_Attack2_info_ball.png",103,103,15);
	m_SnakeMans_Attack2_info_hit=new Sprite(_Device,"data\\image\\SnakeMans_Attack2_info_hit.png",181,201,6);

	m_SnakeMans_attack3=new Sprite(_Device,"data\\image\\SnakeMans_attack3.png",456,371,5);
	m_SnakeMans_Attack3_Ball=new Sprite(_Device,"data\\image\\SnakeMans_Attack3_Ball.png",237,465,5);
	m_SnakeMans_Attack3_Hit=new Sprite(_Device,"data\\image\\SnakeMans_Attack3_Hit.png",216,195,6);

	m_SnakeMans_attack4=new Sprite(_Device,"data\\image\\SnakeMens_attack4.png",328,522,5);
	m_SnakeMans_Attack4_Ball=new Sprite(_Device,"data\\image\\SnakeMans_Attack4_Ball.png",622,563,4);
	m_SnakeMans_Attack4_Hit=new Sprite(_Device,"data\\image\\SnakeMans_Attack4_Hit.png",209,200,6);


	/////////////////////////////////////////
	m_Hero_Move=new Sprite(_Device,"data\\image\\Hero_Move.png",79,103,6);
	m_Hero_Stand=new Sprite(_Device,"data\\image\\Hero_Stand.png",79,98,4);
	m_Hero_Attack1=new Sprite(_Device,"data\\image\\Hero_Attack1.png",570,255,4);
	m_Hero_Attack1_Ball=new Sprite(_Device,"data\\image\\Hero_Attack1_Ball.png",415,143,5);
	m_Hero_Effect1=new Sprite(_Device,"data\\image\\Hero_Attack1_Hit.png",96,113,6);
	m_Hero_Attack2=new Sprite(_Device,"data\\image\\Hero_Attack2.png",294,164,5);
	m_Hero_Attack3=new Sprite(_Device,"data\\image\\Hero_Attack3.png",274,231,5);
	m_Hero_Attack4=new Sprite(_Device,"data\\image\\Hero_Attack4.png",212,251,5);
	m_Hero_Attack3_Ball=new Sprite(_Device,"data\\image\\Hero_Attack3_Ball.png",97,150,7);
	m_Hero_Effect2=new Sprite(_Device,"data\\image\\Hero_Attack3_Hit.png",124,109,5);
	m_Hero_Die=new Sprite(_Device,"data\\image\\Hero_Die.png",212,202,5);

	m_ElephantMove = new Sprite(_Device,"data\\image\\Elephant_Move.png",128,120,8);
	m_ElephantDie = new Sprite(_Device,"data\\image\\ElephantDie.png",178,139,13);
	m_ElephantAttack = new Sprite(_Device,"data\\image\\Elephant_Attack.png",195,193,13);
	m_ElephantHit = new Sprite(_Device,"data\\image\\ElephantHit.png",143,132,1);
	m_ElephantInfo = new Sprite(_Device,"data\\image\\Elephant_Info.png",163,131,4);

	m_SnowManMove = new Sprite(_Device,"data\\image\\SnowMan.png",121,111,4);
	m_SnowManAttack = new Sprite(_Device,"data\\image\\SnowManAttack.png",224,191,9);
	m_SnowManDie = new Sprite(_Device,"data\\image\\SnowMan_Die.png",190,108,7);

	m_SpaceGate = new Sprite(_Device,"data\\image\\SpaceGate.png",300,180,6);
	m_SpaceGate1 = new Sprite(_Device,"data\\image\\SpaceGate_1.png",300,180,6);

	m_Trap = new Sprite(_Device,"data\\image\\Trap.png",72,43,1) ;

	m_BearMove = new Sprite(_Device,"data\\image\\Bear-Move.png",78,87,8) ;
	m_BearDie = new Sprite(_Device,"data\\image\\BearDie.png",146,95,6) ;
	m_BearAttack = new Sprite(_Device,"data\\image\\BearAttack.png",114,104,10) ;

	m_Pet_Move=new Sprite(_Device,"data\\image\\Pet_Hero_Move.png",126,170,10);
	m_Pet_GoAndBack=new Sprite(_Device,"data\\image\\Pet_Hero_GoAndBack.png",126,202,11);
	m_Pet_Attack=new Sprite(_Device,"data\\image\\Pet_Hero_Attack.png",262,226,12);

	m_PirateMove=new Sprite(_Device,"data\\image\\PrivateMove.png",118,107,4);
	m_PirateAttack =new Sprite(_Device,"data\\image\\PrivateAttack.png",159,143,19);
	m_PirateDie =new Sprite(_Device,"data\\image\\PrivateDie.png",162,146,9);

	m_Pharaon = new Sprite(_Device,"data\\image\\Pharaon.png",1010,517,4);
	m_ItemHealth = new Sprite(_Device,"data\\image\\ItemHealth.png",85,78,4);
	m_Skull = new Sprite(_Device,"data\\image\\Skull.png",61,50,7);
}
