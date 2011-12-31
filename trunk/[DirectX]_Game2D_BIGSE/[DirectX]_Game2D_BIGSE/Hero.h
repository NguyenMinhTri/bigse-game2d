#pragma once
#include "character.h"
#include "RSMainGame.h"
class Hero :
	public Character
{
public:
	Sprite* m_SpriteHero;
	InfoSprite m_InfoSpriteHero;
	Sprite* m_SpriteHero_Move;
	InfoSprite m_InfoSpriteHero_Move;
	Sprite* m_SpriteHero_Stand;
	InfoSprite m_InfoSpriteHero_Stand;
	Hero(void);
	~Hero(void);


	virtual void Init();
	virtual void Animation(float _Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);

};

