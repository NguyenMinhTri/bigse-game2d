#pragma once
#include "character.h"
#include "RSMainGame.h"
#include "Arrow.h"
class SnakeMans :
	public Character
{
public:
	int m_VMove;
	float  m_time ;
	virtual void Init();
	virtual void Animation(float _Time);
	virtual void Move (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void UpdateStatus(float _Time);
	virtual void ActiveSkillAuto(float _Time);
	SnakeMans(void);
	~SnakeMans(void);

};

