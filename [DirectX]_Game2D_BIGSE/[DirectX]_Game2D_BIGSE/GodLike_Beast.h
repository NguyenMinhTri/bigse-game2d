#pragma once
#include "Character.h"
class GodLike_Beast :
	public Character
{
protected: 	
	int m_IndexSkill ;
	int m_VMove; 
    Sprite *m_GodLike_Move ;
	Sprite *m_GodLike_Stand ;
	Sprite *m_GodLike_Attack1 ;

	InfoSprite m_InfoSprite1 ;//move
	InfoSprite m_InfoSprite2 ;//stand 
	InfoSprite m_InfoSprite3 ;//skill
public:
	int g_STT ;
	int s_STT ;
	int s1_STT ;

	GodLike_Beast(void);
	~GodLike_Beast(void);
	virtual void Init() ;
	virtual void ProcessCollision(MyObject* _Obj) ;
	virtual void ActiveSkill(int _Index ) ;
	virtual void Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;
	virtual void Animation(float _Time);
	virtual void Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	virtual void Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;
};

