#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "MyObject.h"
#include "Character.h"
#include "Terrain.h"
#include "Global.h"
class Camera
{
	float  m_Width ;
	 float m_Height;
	 float m_X, m_Y;
public :
	 RECT getRect()
	 {
		 RECT r;
		 r.left = m_X ;
		 r.top = m_Y ;
		 r.right = m_X + m_Width;
		 r.bottom = m_Y + m_Height ;

		 return r;
	 }
	 void  Update(Character *_character,Terrain _Terrain)
	 {
		 m_X = _character->getX() - (g_SCREEN_WIDTH - _character->getWidth()  )/2 ;
		 m_Y = _character->getY() - (g_SCREEN_HEIGHT - _character->getHeight())/2 ;
	 }
	 D3DXMATRIX getMatrixTransform ()
	 {
		 D3DXMATRIX MaTrix;

		 D3DXVECTOR2 Center (g_SCREEN_WIDTH/2,g_SCREEN_HEIGHT/2);
		 //D3DXVECTOR2 MTScale(m_ScaleX,m_ScaleY);
		 D3DXVECTOR2 MTTran (-m_X,-m_Y); //

		 float Rota = (float)(m_Ro*2*D3DX_PI)/(float)(360);

		 D3DXMatrixTransformation2D(&MaTrix,&Center,0,&MTScale,&Center,Rota,&MTTran);
		 return MaTrix;
	 }
	 
};