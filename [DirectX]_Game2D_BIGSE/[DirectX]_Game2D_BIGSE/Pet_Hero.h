#pragma once
#include "myobject.h"
#include "Skill.h"
#include "Global.h"
#include "Character.h"
class Pet_Hero :
	public Character
{
public:
	int m_VMove;
	P_STT p_stt;
	float  m_TimeLife ;
	float m_TimeCoolDown;
	MyObject *m_Character ;
	Sprite* m_Sprite_Move;
	InfoSprite m_InfoSprite_Move;
	Sprite* m_Sprite_GoAndBack;
	InfoSprite m_InfoSprite_GoAndBack;
	Sprite* m_Sprite_Attack;
	InfoSprite m_InfoSprite_Attack;
	Sprite* m_Sprite_Pet;
	InfoSprite m_InfoSprite_Pet;
	int m_VFly;

	Pet_Hero(MyObject*  _Character);
	~Pet_Hero(void);
	virtual void Init();
	virtual void Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Active();
	virtual void Animation(float __Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void ProcessCollision(MyObject* _Obj);
	virtual void UpdateStatus(float _Time);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);
	virtual void AutoSkill(float _Time);
	virtual void ActiveSkill(float _X,float _Y);
	virtual void GO();
};

