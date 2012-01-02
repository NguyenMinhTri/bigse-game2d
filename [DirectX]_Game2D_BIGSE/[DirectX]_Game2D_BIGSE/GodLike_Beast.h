#pragma once
#include "Character.h"
class GodLike_Beast :
	public Character
{
protected: 	
	int m_IndexSkill ;
	int m_VMove; 

	float m_TimePrivate   ;
	float  m_time ;
    Sprite *m_GodLike_Move ;
	Sprite *m_GodLike_Stand ;

	InfoSprite m_InfoSprite1 ;//move
	InfoSprite m_InfoSprite2 ;//stand 
public:
	int g_STT ;
	GodLike_Beast(void);
	~GodLike_Beast(void);

	virtual void Init() ;
	virtual void ProcessCollision(MyObject* _Obj) ;
	virtual void ActiveSkill(int _Index);
	virtual void Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;
	virtual void Animation(float _Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void UpdateStatus(float _Time);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;
};

