#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "MyObject.h"
#include "Character.h"

class Terrain
{
	int **m_Terrain ;
	int m_Width;
	int m_Height ;
	Terrain (int** _Terrain, int _Width,int _Height )
	{
		m_Terrain = _Terrain ;
		m_Width = _Width ;
		m_Height = _Height;
	}
	int getWidth ()
	{
		return m_Width;
	}
	int getHeight ()
	{
		return m_Height;
	}


};