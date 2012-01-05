#pragma once
#include "monster.h"
#include "Character.h"
#include "RSMainGame.h"
class SnowMan :
	public Monster
{
private:
	Sprite *m_SnowManMove ;
	InfoSprite m_InfoMove ;

public:
	SnowMan(void);
	~SnowMan(void);
	virtual void Init () ;
	/* Processing collision */
	virtual void ProcessCollision (MyObject* _Obj);

	/* Check collision with other Object */

	/* Update Animation */
	void Animation (float _Time) ;

	/* Update Status */
	virtual void UpdateStatus (float _Time) ;

	/* Update all */
	virtual void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) ;
	/* Release */
	virtual void Release () ;
};