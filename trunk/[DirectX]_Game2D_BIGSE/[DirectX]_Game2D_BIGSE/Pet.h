#pragma once
#include "myobject.h"
#include "Skill.h"
#include "Global.h"
#include "Character.h"

class Pet :
	public Skill
{
protected:
	float  m_TimeLife ;
	float m_TimeCoolDown;
	float m_TimeShoot ;
	MyObject *m_Character ;
	Sprite* m_Partner;
public:
 	Pet(MyObject* _Character);
	~Pet(void);
	virtual void Init();
	virtual void Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Active(float _X,float _Y,int _Dir);
	virtual void Animation(float __Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void ProcessCollision(MyObject* _Obj);
	virtual void UpdateStatus(float _Time);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);
};

