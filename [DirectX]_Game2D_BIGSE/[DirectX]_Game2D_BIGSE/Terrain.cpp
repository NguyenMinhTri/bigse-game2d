#include "Terrain.h"
#include "Camera.h"


Terrain::Terrain(void)
{
}


Terrain::~Terrain(void)
{
}
Terrain::Terrain (int** _Terrain, int _Width,int _Height )
{
	m_Terrain = _Terrain ;
	m_Width = _Width ;
	m_Height = _Height;
	m_Sprite = RSMainGame::get()->getTerrain();
}
void Terrain::Draw (Camera* _Camera,D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	for (int i = _Camera->getRect().Left/g_CELL; i < (_Camera->getRect().Right)/g_CELL  ; i++)
	{
		for (int j = _Camera->getRect().Top/g_CELL; j<(_Camera->getRect().Bottom)/g_CELL ;j++)
		{
			if (m_Terrain[i][j]!= 0)
			{
				m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL,j*g_CELL-10,0,0.2f);
			}
		}
	}
}