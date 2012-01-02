#include "Terrain.h"
#include "Camera.h"


Terrain::Terrain(void)
{
}


Terrain::~Terrain(void)
{
}
Terrain::Terrain (int** _Terrain,int** _TerrainExtends, int _Width,int _Height )
{
	m_Width = _Width ;
	m_Height = _Height;
	m_Terrain = _Terrain ;
	m_TerrainExtends = _TerrainExtends;
	m_Sprite = RSMainGame::get()->getGrass();
	m_Sprite2 = RSMainGame::get()->getGrass2();
	m_IC = RSMainGame::get()->getIC();
	m_IC2 = RSMainGame::get()->getIC2();
}
void Terrain::Draw (Camera* _Camera,D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	for (int i = _Camera->getRect().Left/g_CELL; i < (_Camera->getRect().Right)/g_CELL  ; i++)
	{
		for (int j = _Camera->getRect().Top/g_CELL; j<(_Camera->getRect().Bottom)/g_CELL ;j++)
		{
			if (m_TerrainExtends[i][j]>=200 && m_TerrainExtends[i][j]<=234)
			{
				if(m_TerrainExtends[i][j]==200)
				m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,0,0.6f);
				if(m_TerrainExtends[i][j]==201)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,1,0.6f);
				if(m_TerrainExtends[i][j]==202)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,2,0.6f);
				if(m_TerrainExtends[i][j]==205)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,3,0.6f);
				if(m_TerrainExtends[i][j]==206)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,4,0.6f);
				if(m_TerrainExtends[i][j]==207)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,5,0.6f);
				if(m_TerrainExtends[i][j]==208)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,6,0.6f);
				if(m_TerrainExtends[i][j]==209)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,7,0.6f);
				if(m_TerrainExtends[i][j]==210)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,8,0.6f);
				if(m_TerrainExtends[i][j]==211)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,9,0.6f);
				if(m_TerrainExtends[i][j]==212)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,10,0.6f);
				if(m_TerrainExtends[i][j]==213)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,11,0.6f);
				if(m_TerrainExtends[i][j]==214)
					m_Sprite->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,12,0.6f);

				if(m_TerrainExtends[i][j]==203)
					m_Sprite2->Draw(_Handler,_mtWorld,i*g_CELL,j*g_CELL,1,0.6f);
				if(m_TerrainExtends[i][j]==204)
					m_Sprite2->Draw(_Handler,_mtWorld,i*g_CELL,j*g_CELL,0,0.6f);
				//////////////////////////////////////////////////////////////////////////
				if(m_TerrainExtends[i][j]==220)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,0,0.6f);
				if(m_TerrainExtends[i][j]==221)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,1,0.6f);
				if(m_TerrainExtends[i][j]==222)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,2,0.6f);
				if(m_TerrainExtends[i][j]==225)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,3,0.6f);
				if(m_TerrainExtends[i][j]==226)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,4,0.6f);
				if(m_TerrainExtends[i][j]==227)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,5,0.6f);
				if(m_TerrainExtends[i][j]==228)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,6,0.6f);
				if(m_TerrainExtends[i][j]==229)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,7,0.6f);
				if(m_TerrainExtends[i][j]==230)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,8,0.6f);
				if(m_TerrainExtends[i][j]==231)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,9,0.6f);
				if(m_TerrainExtends[i][j]==232)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,10,0.6f);
				if(m_TerrainExtends[i][j]==233)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,11,0.6f);
				if(m_TerrainExtends[i][j]==234)
					m_IC->Draw(_Handler,_mtWorld,i*g_CELL-1,j*g_CELL,12,0.6f);

				if(m_TerrainExtends[i][j]==223)
					m_IC2->Draw(_Handler,_mtWorld,i*g_CELL,j*g_CELL,0,0.6f);
				if(m_TerrainExtends[i][j]==224)
					m_IC2->Draw(_Handler,_mtWorld,i*g_CELL,j*g_CELL,1,0.6f);
			}
		}
	}
}