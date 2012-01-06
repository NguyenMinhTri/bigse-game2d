#pragma once
#include "character.h"
#include "RSMainGame.h"
#include "Pet_Hero.h"
class Hero :
	public Character
{
public:
	Pet_Hero* m_Pet;
	Sprite* m_SpriteHero;
	Sprite* m_Hero_Die;
	InfoSprite m_InfoHero_Die;
	InfoSprite m_InfoSpriteHero;
	Sprite* m_SpriteHero_Move;
	InfoSprite m_InfoSpriteHero_Move;
	Sprite* m_SpriteHero_Stand;
	InfoSprite m_InfoSpriteHero_Stand;
	Hero(void);
	~Hero(void);

	virtual void CallPet();
	virtual void Init();
	virtual void Animation(float _Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);

};

