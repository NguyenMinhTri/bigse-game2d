#pragma once
#include "InfoSprite.h"
#include "Sprite.h"
class MyObject
{
protected:
	/* ID of Object */
	int m_ID;

	/* Status */
	int m_STT,m_OldSTT;

	/* Position */
	float m_X,m_Y;

	/* Velocity */
	float m_Vx, m_Vy;

	/* Size */
	float m_Width,m_Height;

	/* Time for Update */
	float m_TimeUpdate;

	/* Time for Animation */
	float m_TimeAni;

	/* All information sprite for render*/
	InfoSprite m_InfoSprite;
	/*Sprite m_Sprite;*/

public:
	MyObject(void);
	virtual ~MyObject(void);

	void setID (int _id) { m_ID = _id;}
	void setX (float _X) { m_X = _X;}
	void setY (float _Y){
		m_Y = _Y;
	}
	void setXY (float _X, float _Y){
		m_X = _X;
		m_Y = _Y;
	}
	void setSize (float _SizeX, float _SizeY){
		m_Width = _SizeX;
		m_Height = _SizeY;
	}

	float getX () { return m_X;}
	float getY () { return m_Y;}

	float getWidth()
	{
		return m_Width ;
	}
	float getHeight()
	{
		return m_Height ;
	}
	int getSTT () {return m_STT;}
	int getOldSTT () {return m_OldSTT;}

	int getID () { return m_ID;}

	virtual void Init () = 0;
	/* Processing collision */
	virtual void ProcessCollision (MyObject* _Obj) = 0;

	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) = 0;

	/* Update Move and check Collision with Terrain */
	virtual void Move (float _Time, int** _Terrain) = 0;

	/* Update Animation */
	virtual void Animation (float _Time) = 0;

	/* Update status */
	virtual void UpdateStatus (float _Time) = 0;

	/* Update all */
	virtual void Update (float _Time) =0 ;

	/* Draw Object */
	virtual void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler) = 0;

	/* Release */
	virtual void Release () = 0;
};

