#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
class RSMainGame
{
private:
	static RSMainGame* instance ; 
	Sprite* m_IC;
	Sprite* m_IC2;
	Sprite* m_Grass;
	Sprite* m_Grass2;
	Sprite* m_FontNum;
	Sprite* m_Character;
	Sprite* m_Terrain;
	Sprite* m_Frenzy;
	Sprite* m_Pet ;
	Sprite* m_Archer ;
	Sprite* m_Arrow ;
	Sprite* m_Magician;
	Sprite* m_medicine;
	Sprite* m_Partner;
	Sprite* m_Angle ;
	Sprite* m_Thunder1;
	Sprite* m_Thunder2;
	Sprite* m_EffectIce ;
	Sprite* m_EffectDie ;
	Sprite* m_FrenzyTime ;
	Sprite* m_GodLikeMove ;
	Sprite* m_GodLikeStand ;
	Sprite* m_GodLikeAttack1 ;
	Sprite* m_GodLikeAttack2 ;
	Sprite* m_GodLikeAttack3 ;
	Sprite* m_GodLikeAttack4_1;
	Sprite* m_GodLikeAttack4_2;
	Sprite* m_EffectLaze ;
	Sprite* m_EffectSound ;
	Sprite* m_EffectThunder ;
	Sprite* m_EffectHit ;
	Sprite* m_EffectLeonDie_1 ;
	Sprite* m_EffectLeonDie_2 ;
	Sprite* m_Teleport ;
	Sprite* m_Teleport1 ;
	////////////////////////////////
	Sprite* m_SnakeMans_Move;
	Sprite* m_SnakeMans_Die;
	
	Sprite* m_SnakeMans_attack1;
	Sprite* m_SnakeMans_Attack1_Hit;


	Sprite* m_ElephantMove;
	Sprite* m_ElephantDie;
	Sprite* m_ElephantAttack ;
	Sprite* m_ElephantInfo ;
	Sprite* m_ElephantHit ;

	Sprite* m_SnakeMans_attack2;
	Sprite* m_SnakeMans_Attack2_info_ball;
	Sprite* m_SnakeMans_Attack2_info_hit;

	Sprite* m_SnowManMove ;
	Sprite* m_SnowManDie ;
	Sprite* m_SnowManAttack ;
	Sprite* m_SnakeMans_attack3;
	Sprite* m_SnakeMans_Attack3_Ball;
	Sprite* m_SnakeMans_Attack3_Hit;

	Sprite* m_SnakeMans_attack4;
	Sprite* m_SnakeMans_Attack4_Ball;
	Sprite* m_SnakeMans_Attack4_Hit;
	////////////////////////////////
	Sprite* m_Hero_Move;
	Sprite* m_Hero_Stand;
	Sprite* m_Hero_Attack1;
	Sprite* m_Hero_Attack1_Ball;
	Sprite* m_Hero_Effect1;
	Sprite* m_Hero_Attack2;
	Sprite* m_Hero_Attack3;
	Sprite* m_Hero_Attack4;
	Sprite* m_Hero_Attack3_Ball;
	Sprite* m_Hero_Effect2;
	Sprite* m_Hero_Die;

	Sprite* m_SpaceGate ;
	Sprite* m_SpaceGate1;
	Sprite* m_Trap ;

	Sprite* m_BearMove ;
	Sprite* m_BearDie ;
	Sprite* m_BearAttack ;
	Sprite* m_WorldMap ;

	//////////////////////////
	Sprite* m_Pet_Move;
	Sprite* m_Pet_GoAndBack;
	Sprite* m_Pet_Attack;

	RSMainGame(void);
public:
	
	~RSMainGame(void);
	static RSMainGame* get (){
		if (instance == NULL)
		{
			instance = new RSMainGame();
		}
		return instance;
	}
	void IntRS (LPDIRECT3DDEVICE9 _Device);
	void Release ();

	Sprite* getCharacter (){
		return m_Character;
	}
	Sprite* getTerrain (){
		return m_Terrain;
	}
	Sprite* getFrenzy(){
		return m_Frenzy;
	}
	Sprite* getPet(){
		return m_Pet;
	}
	Sprite* getArcher(){
		return m_Archer ;
	}
	Sprite* getArrow(){
		return m_Arrow ;
	}
	Sprite* getMagician(){
		return m_Magician ;
	}
	Sprite* getMedicine()
	{
		return m_medicine;
	}
	Sprite* getPartner()
	{
		return  m_Partner;
	}
	Sprite* getAngle()
	{
		return  m_Angle;
	}
	Sprite* getThunder1()
	{
		return  m_Thunder1;
	}
	Sprite* getThunder2()
	{
		return  m_Thunder2;
	}
	Sprite* getEffectIce()
	{
		return m_EffectIce ;
	}
	Sprite* getEffectDie()
	{
		return m_EffectDie;
	}
	Sprite* getFrenzyTime()
	{
		return m_FrenzyTime ;
	}
	Sprite* getGodLikeMove()
	{
		return m_GodLikeMove ;
	}
	Sprite* getGodLikeStand()
	{
		return m_GodLikeStand ;
	}
	Sprite* getGodLikeAttack1()
	{
		return m_GodLikeAttack1 ;
	}
	Sprite* getGodLikeAttack2()
	{
		return m_GodLikeAttack2 ;
	}
	Sprite* getGodLikeAttack3()
	{
		return m_GodLikeAttack3 ;
	}

	Sprite* getGodLikeAttack4_1()
	{
		return m_GodLikeAttack4_1 ; //dang lam`
	}

	Sprite* getGodLikeAttack4_2()
	{
		return m_GodLikeAttack4_2 ;
	}

	Sprite* getSnakeMans_Move()
	{
		return m_SnakeMans_Move ;
	}

	Sprite* getHero_Move()
	{
		return m_Hero_Move;
	}
	Sprite* getHero_Stand()
	{
		return m_Hero_Stand;
	}
	Sprite* getHero_Attack1()
	{
		return m_Hero_Attack1;
	}
	Sprite* getHero_Attack1_Ball()
	{
		return m_Hero_Attack1_Ball;
	}
	Sprite* getHero_Effect1()
	{
		return m_Hero_Effect1;
	}
	Sprite* getHero_Attack2()
	{
		return m_Hero_Attack2;
	}
	Sprite* getHero_Attack3()
	{
		return m_Hero_Attack3;
	}
	Sprite* getHero_Attack4()
	{
		return m_Hero_Attack4;
	}
	Sprite* getHero_Attack3_Ball()
	{
		return m_Hero_Attack3_Ball;
	}
	Sprite* getHero_Effect2()
	{
		return m_Hero_Effect2;
	}
	Sprite* getHero_Die()
	{
		return m_Hero_Die;
	}
	Sprite* getEffectLaze()
	{
		return m_EffectLaze;
	}
	Sprite* getEffectSound()
	{
		return m_EffectSound;
	}
	Sprite* getEffectThunder()
	{
		return m_EffectThunder;
	}
	Sprite* getEffectHit()
	{
		return m_EffectHit;
	}
	Sprite* getEffectLeonDie_1()
	{
		return m_EffectLeonDie_1;
	}
	Sprite* getEffectLeonDie_2()
	{
		return m_EffectLeonDie_2;
	}
	Sprite* getTeleport()
	{
		return m_Teleport ;
	}
	Sprite* getTeleport1()
	{
		return m_Teleport1 ;
	}
	Sprite* getNumFont()
	{
		return m_FontNum;
	}
	Sprite* getGrass()
	{
		return m_Grass;
	}
	Sprite* getGrass2()
	{
		return m_Grass2;
	}
	Sprite* getIC()
	{
		return m_IC;
	}
	Sprite* getIC2()
	{
		return m_IC2;
	}
	Sprite* getElephantMove()
	{
		return m_ElephantMove ;
	}
	Sprite* getElephantAttack()
	{
		return m_ElephantAttack ;
	}
	Sprite* getElephantDie()
	{
		return m_ElephantDie ;
	}
	Sprite* getElephantInfo()
	{
		return m_ElephantInfo ;
	}
	Sprite* getElephantHit()
	{
		return m_ElephantHit ;
	}

	Sprite* getSnowManMove()
	{
		return m_SnowManMove ;
	}
	Sprite* getSnowManAttack()
	{
		return m_SnowManAttack ;
	}
	Sprite* getSnowManDie()
	{
		return m_SnowManDie ;
	}
	Sprite* getSnakeMans_Die()
	{
		return m_SnakeMans_Die;
	}
	Sprite* getSnakeMans_attack1()
	{
		return m_SnakeMans_attack1;
	}
	Sprite* getSnakeMans_Attack1_Hit()
	{
		return m_SnakeMans_Attack1_Hit;
	}
	Sprite* getSnakeMans_Attack2()
	{
		return m_SnakeMans_attack2;
	}
	Sprite* getSnakeMans_Attack2_Ball()
	{
		return m_SnakeMans_Attack2_info_ball;
	}
	Sprite* getSnakeMans_Attack2_Hit()
	{
		return m_SnakeMans_Attack2_info_hit;
	}
	Sprite* getSnakeMans_Attack3()
	{
		return m_SnakeMans_attack3;
	}
	Sprite* getSnakeMans_Attack3_Ball()
	{
		return m_SnakeMans_Attack3_Ball;
	}
	Sprite* getSnakeMans_Attack3_Hit()
	{
		return m_SnakeMans_Attack3_Hit;
	}
	Sprite* getSnakeMans_Attack4()
	{
		return m_SnakeMans_attack4;
	}
	Sprite* getSnakeMans_Attack4_Ball()
	{
		return m_SnakeMans_Attack4_Ball;
	}
	Sprite* getSnakeMans_Attack4_Hit()
	{
		return m_SnakeMans_Attack4_Hit;
	}
	Sprite* getSpaceGate()
	{
		return m_SpaceGate ;
	}
	Sprite* getSpaceGate_1()
	{
		return m_SpaceGate1 ;
	}
	Sprite* getTrap()
	{
		return m_Trap ;
	}

	Sprite* getBearMove()
	{
		return m_BearMove ;
	}
	Sprite* getBearDie()
	{
		return m_BearDie ;
	}
	Sprite* getBearAttack()
	{
		return m_BearAttack ;
	}
	Sprite* getWorldMap()
	{
		return m_WorldMap ;
	}
	Sprite* getPet_Move()
	{
		return m_Pet_Move;
	}
	Sprite* getPet_GoAndBack()
	{
		return m_Pet_GoAndBack;
	}
	Sprite* getPet_Attack()
	{
		return m_Pet_Attack;
	}
};

