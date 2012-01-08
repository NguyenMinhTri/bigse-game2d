#pragma once
#include "MyObject.h"
#include "RSMainGame.h"
#include "Global.h"

class Camera;

class Terrain
{
private:
	int **m_Terrain ;
	int **m_TerrainExtends ;
	int m_Width;
	int m_Height;
	Sprite* m_Sprite;
	Sprite* m_Sprite2;

	Sprite* m_IC;
	Sprite* m_IC2;
	Sprite* m_100;
	Sprite* m_101;
	Sprite* m_102;
	Sprite* m_103;
	Sprite* m_104;
	Sprite* m_105;
	Sprite* m_106;
	Sprite* m_107;
	Sprite* m_108;
	Sprite* m_109;
	Sprite* m_110;
	Sprite* m_111;
	Sprite* m_112;
	Sprite* m_113;
	Sprite* m_114;
	Sprite* m_115;
	Sprite* m_116;
	Sprite* m_117;
	Sprite* m_118;
	Sprite* m_119;
	Sprite* m_120;
	Sprite* m_121;
	Sprite* m_122;
	Sprite* m_123;
	Sprite* m_124;
	Sprite* m_125;
	Sprite* m_126;
	Sprite* m_127;
	Sprite* m_128;
	Sprite* m_129;
	Sprite* m_130;
	Sprite* m_131;
public:
	Terrain(void);
	~Terrain(void);
	Terrain (int** _Terrain,int** _TerrainExtends, int _Width,int _Height );
	
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

