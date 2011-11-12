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
	for (int i = _Camera->getRect().left/g_CELL; i < (_Camera->getRect().right)/g_CELL+1  ; i++)
	{
		for (int j = _Camera->getRect().top/g_CELL; j<(_Camera->getRect().bottom)/g_CELL+1 ;j++)
		{
			if (m_Terrain[i][j]!= 0)
			{
				m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL,j*g_CELL-10,0);
			}
		}
	}
}