#pragma once
#include "Character.h"
#include "Global.h"
#include "Terrain.h"
class Camera
{
private:
	float	m_Width ;
	float	m_Height;
	float	m_X, m_Y;
	

	float m_Dy,m_VDy;
	float m_SC;

public:
	Camera(void);
	Camera (float _X, float _Y,float _Width,float _Height);
	~Camera(void);

	float getX ()
	{
		return m_X;
	};
	float getY ()
	{
		return m_Y;
	};

	float getWidth ()
	{
		return m_Width;
	};

	float getHeight ()
	{
		return m_Height;
	};

	 RECT getRect()
	 {
		 RECT r;
		 r.left = m_X ;
		 r.top = m_Y ;
		 r.right = m_X + m_Width;
		 r.bottom = m_Y + m_Height ;

		 return r;
	 };
	 void  Update(Character* _Character,float _MaxWidth,float _MaxHeight);
	 void UpdateEffect (float _Time);

	 D3DXMATRIX getMatrixTransform ();
};

