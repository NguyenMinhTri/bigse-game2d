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
	
	float	m_Offset;

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

	 CRECT getRect()
	 {
		 CRECT r;
		 r.Left = m_X - m_Offset ;
		 r.Top = m_Y - m_Offset;
		 r.Right = m_X + m_Width + m_Offset;
		 r.Bottom = m_Y + m_Height + m_Offset ;

		 return r;
	 };
	 void  Update(Character* _Character,float _MaxWidth,float _MaxHeight);
	 void UpdateEffect (float _Time);
	 void NoEffect ();
	 D3DXMATRIX getMatrixTransform ();
};

