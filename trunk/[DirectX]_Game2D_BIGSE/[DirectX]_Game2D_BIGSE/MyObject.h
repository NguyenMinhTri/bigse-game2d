#pragma once
#include <list>

#include "InfoSprite.h"
#include "RECT.h"
#include "Sprite.h"
#include "Effect.h"
/*#include "Terrain.h"*/
class MyObject
{
protected:
	/* ID of Object */
	int m_ID;

    int m_HP;
    int m_Damage;


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
	bool m_iFrenzy;
	bool m_iFire;
	bool m_iLife;
	bool m_iActive ;

	Effect m_Effect;
public:
	MyObject(void);
	virtual ~MyObject(void);
 	CRECT getRect(){
		CRECT r;
		r.Left = m_X ;
		r.Top = m_Y ;
		r.Right = m_X + m_Width;
		r.Bottom = m_Y + m_Height ;

		return r;
	}

	int getHp ()
	{
		return m_HP;
	}

	void setHp (int _hp)
	{
		m_HP = _hp ;
	}

	void setID (int _id) { m_ID = _id;}
	void setX (float _X) { m_X = _X;}
	void setY (float _Y){
		m_Y = _Y;
	}
	void setXY (float _X, float _Y){
		m_X = _X;
		m_Y = _Y;
	}
	void setSize (float _width, float _height){
		m_Width = _width;
		m_Height = _height;
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

	bool getFrenzy(){
		return m_iFrenzy ;
	}
	void setFrenzey(bool _frenzy){
		m_iFrenzy = _frenzy ;
	}
	bool getFire(){
		return m_iFire ;
	}

	void setFire (bool _Fire){
		m_iFire = _Fire;
	}

	bool getActive(){
		return m_iActive;
	}

	void setActive (bool _active){
		m_iActive = _active ;
	}

	bool getLife(){
		return m_iLife;
	}

	void setLife (bool _Life){
		m_iLife = _Life;
	}
	InfoSprite getInfoSprite ()
	{
		return m_InfoSprite;
	}
	virtual void Init () = 0;
	/* Processing collision */
	virtual void ProcessCollision (MyObject* _Obj) = 0;

	/* Check collision with other Object */
	virtual bool iCollision (MyObject* _Obj) = 0;

	/* Update Move and check Collision with Terrain */
	virtual void Move (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight) = 0;

	/* Update Move and check Collision with Terrain */
	//virtual void Move (float _Time, Terrain* _Map){} ;

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

