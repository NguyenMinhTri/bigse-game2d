#pragma once
#include "MyObject.h"
#include "RSMainGame.h"
#include "Global.h"

class Camera;

class Terrain
{
private:
	int **m_Terrain ;
	int m_Width;
	int m_Height;
	Sprite* m_Sprite;
public:
	Terrain(void);
	~Terrain(void);
	Terrain (int** _Terrain, int _Width,int _Height );
	
	int getWidth ()
	{
		return m_Width;
	}
	int getHeight ()
	{
		return m_Height;
	}
	int** getTerrain ()
	{
		return m_Terrain;
	}
	void Draw (Camera* _Camera,D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler);
};

