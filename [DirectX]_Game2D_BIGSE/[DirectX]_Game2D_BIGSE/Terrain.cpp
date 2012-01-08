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

	m_100 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\100.png",367,283,1);
	m_101 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\101.png",195,186,1);
	m_102 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\102.png",280,107,1);
	m_103 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\103.png",150,66,1);
	m_104 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\104.png",92,52,1);
	m_105 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\105.png",97,168,1);
	m_106 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\106.png",219,215,1);
	m_107 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\107.png",204,224,1);
	m_108 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\108.png",173,112,1);
	m_109 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\109.png",157,172,1);
	m_110 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\110.png",96,105,1);
	m_111 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\111.png",265,325,1);
	m_112 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\112.png",274,261,1);
	m_113 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\113.png",366,392,1);
	m_114 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\114.png",268,252,1);
	m_115 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\115.png",232,285,1);
	m_116 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\116.png",216,274,1);
	m_117 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\117.png",244,387,1);
	m_118 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\118.png",191,237,1);
	m_119 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\119.png",357,190,1);
	m_120 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\120.png",80,137,1);
	m_121 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\121.png",62,100,1);
	m_122 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\122.png",309,307,1);
	m_123 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\123.png",96,120,1);
	m_124 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\124.png",136,108,1);
	m_125 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\125.png",134,134,1);
	m_126 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\126.png",244,290,1);
	m_127 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\127.png",575,410,1);
	m_128 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\128.png",424,398,1);
	m_129 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\129.png",408,332,1);
	m_130 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\130.png",567,531,1);
	m_131 = new Sprite(DXManager::Instance()->getDevice(),
		"data\\image\\131.png",517,537,1);
}
void Terrain::Draw (Camera* _Camera,D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	
	for (int i = _Camera->getRect().Left/g_CELL; i < (_Camera->getRect().Right)/g_CELL  ; i++)
	{
		if (i<0 || i >= m_Width)
		{
			continue;
		}
		for (int j = _Camera->getRect().Top/g_CELL; j<(_Camera->getRect().Bottom)/g_CELL ;j++)
		{
			if (j<0 || j>= m_Height)
			{
				continue;
			}
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
			if(m_TerrainExtends[i][j]==100)
				m_100->Draw(_Handler,_mtWorld,i*g_CELL-158,j*g_CELL-183,0,0.59f);

			if(m_TerrainExtends[i][j]==101)
				m_101->Draw(_Handler,_mtWorld,i*g_CELL-72,j*g_CELL-86,0,0.59f);
			if(m_TerrainExtends[i][j]==102)
				m_102->Draw(_Handler,_mtWorld,i*g_CELL-115,j*g_CELL-07,0,0.59f);
			if(m_TerrainExtends[i][j]==103)
				m_103->Draw(_Handler,_mtWorld,i*g_CELL-50,j*g_CELL+34,0,0.59f);
			if(m_TerrainExtends[i][j]==104)
				m_104->Draw(_Handler,_mtWorld,i*g_CELL-20,j*g_CELL+48,0,0.59f);
			if(m_TerrainExtends[i][j]==105)
				m_105->Draw(_Handler,_mtWorld,i*g_CELL-23,j*g_CELL-68,0,0.59f);
			if(m_TerrainExtends[i][j]==106)
				m_106->Draw(_Handler,_mtWorld,i*g_CELL-84,j*g_CELL-115,0,0.59f);
			if(m_TerrainExtends[i][j]==107)
				m_107->Draw(_Handler,_mtWorld,i*g_CELL-75,j*g_CELL-124,0,0.59f);
			if(m_TerrainExtends[i][j]==108)
				m_108->Draw(_Handler,_mtWorld,i*g_CELL-61,j*g_CELL-12,0,0.59f);
			if(m_TerrainExtends[i][j]==109)
				m_109->Draw(_Handler,_mtWorld,i*g_CELL-53,j*g_CELL-71,0,0.59f);
			if(m_TerrainExtends[i][j]==110)
				m_110->Draw(_Handler,_mtWorld,i*g_CELL-23,j*g_CELL-5,0,0.59f);
			if(m_TerrainExtends[i][j]==111)
				m_111->Draw(_Handler,_mtWorld,i*g_CELL-107,j*g_CELL-225,0,0.59f);
			if(m_TerrainExtends[i][j]==112)
				m_112->Draw(_Handler,_mtWorld,i*g_CELL-112,j*g_CELL-161,0,0.59f);
			if(m_TerrainExtends[i][j]==113)
				m_113->Draw(_Handler,_mtWorld,i*g_CELL-158,j*g_CELL-292,0,0.59f);
			if(m_TerrainExtends[i][j]==114)
				m_114->Draw(_Handler,_mtWorld,i*g_CELL-109,j*g_CELL-152,0,0.59f);
			if(m_TerrainExtends[i][j]==115)
				m_115->Draw(_Handler,_mtWorld,i*g_CELL-91,j*g_CELL-185,0,0.59f);
			if(m_TerrainExtends[i][j]==116)
				m_116->Draw(_Handler,_mtWorld,i*g_CELL-85,j*g_CELL-174,0,0.59f);
			if(m_TerrainExtends[i][j]==117)
				m_117->Draw(_Handler,_mtWorld,i*g_CELL-97,j*g_CELL-284,0,0.59f);
			if(m_TerrainExtends[i][j]==118)
				m_118->Draw(_Handler,_mtWorld,i*g_CELL-70,j*g_CELL-137,0,0.59f);
			if(m_TerrainExtends[i][j]==119)
				m_119->Draw(_Handler,_mtWorld,i*g_CELL-84,j*g_CELL-90,0,0.59f);
			if(m_TerrainExtends[i][j]==120)
				m_120->Draw(_Handler,_mtWorld,i*g_CELL-16,j*g_CELL-37,0,0.59f);
			if(m_TerrainExtends[i][j]==121)
				m_121->Draw(_Handler,_mtWorld,i*g_CELL-6,j*g_CELL-0,0,0.59f);
			if(m_TerrainExtends[i][j]==122)
				m_122->Draw(_Handler,_mtWorld,i*g_CELL-130,j*g_CELL-207,0,0.59f);
			if(m_TerrainExtends[i][j]==123)
				m_123->Draw(_Handler,_mtWorld,i*g_CELL-23,j*g_CELL-20,0,0.59f);
			if(m_TerrainExtends[i][j]==124)
				m_124->Draw(_Handler,_mtWorld,i*g_CELL-43,j*g_CELL-8,0,0.59f);
			if(m_TerrainExtends[i][j]==125)
				m_125->Draw(_Handler,_mtWorld,i*g_CELL-42,j*g_CELL-34,0,0.59f);
			if(m_TerrainExtends[i][j]==126)
				m_126->Draw(_Handler,_mtWorld,i*g_CELL-97,j*g_CELL-190,0,0.59f);
			if(m_TerrainExtends[i][j]==127)
				m_127->Draw(_Handler,_mtWorld,i*g_CELL-262,j*g_CELL-310,0,0.59f);
			if(m_TerrainExtends[i][j]==128)
				m_128->Draw(_Handler,_mtWorld,i*g_CELL-187,j*g_CELL-298,0,0.59f);
			if(m_TerrainExtends[i][j]==129)
				m_129->Draw(_Handler,_mtWorld,i*g_CELL-179,j*g_CELL-232,0,0.59f);
			if(m_TerrainExtends[i][j]==130)
				m_130->Draw(_Handler,_mtWorld,i*g_CELL-258,j*g_CELL-431,0,0.59f);
			if(m_TerrainExtends[i][j]==131)
				m_131->Draw(_Handler,_mtWorld,i*g_CELL-233,j*g_CELL-437,0,0.59f);

		}
	}
}