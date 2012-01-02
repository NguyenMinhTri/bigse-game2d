#include "LoadMap.h"
#define getA© ((©&0xff000000)>>24)
#define getR© ((©&0x00ff0000)>>16)
#define getG© ((©&0x0000ff00)>>8)
#define getB© (©&0x000000ff)
#include "GodLike_Beast.h"
#include "ManagerObject.h"
#include "Monster.h"

LoadMap::LoadMap(void)
{
	m_Width = 0;
	m_Height = 0;
}


LoadMap::~LoadMap(void)
{
}

HRESULT LoadMap::LoadMapFormFile(LPCTSTR _file, LPDIRECT3DDEVICE9 _Device)
{
	HRESULT	hr;
	D3DXIMAGE_INFO imageInfo;
	hr = D3DXGetImageInfoFromFile( _file , &imageInfo );

	if(FAILED(hr))
		return hr;

	//Create a raw map as a texture file with a 32-bit format
	hr = D3DXCreateTextureFromFileEx( _Device ,							// DirectX device
		_file ,							    // File Path
		imageInfo.Width ,					// width
		imageInfo.Height ,					// Height
		imageInfo.MipLevels ,				// MipLevels
		D3DUSAGE_DYNAMIC ,					// D3DUSAGE
		D3DFMT_A8R8G8B8 ,					// Format
		D3DPOOL_DEFAULT ,					// Pool
		D3DX_DEFAULT ,						// Filter
		D3DX_DEFAULT ,						// Mip filter
		0 ,									// Color key
		&imageInfo ,						// Image Info
		NULL ,								// NULL
		&m_MapTex );							// Output texture

	//Store the raw map width and height
	m_Width		= imageInfo.Width;
	m_Height	= imageInfo.Height;


	if(FAILED(hr))
		return hr;

	return S_OK;
}
void LoadMap::TranslateMap()
{
	HRESULT hr;
	D3DLOCKED_RECT rect;
	D3DSURFACE_DESC desc;
	DWORD i,j;
	D3DCOLOR** pColor;

	//First get the D3DSURFACE_DESC of this raw map
	hr = m_MapTex->GetLevelDesc( 0 , &desc );
	if(FAILED(hr))
		return ;

	//We create a new D3DCOLOR 2D array has enough room to hold pixel color 
	pColor = new D3DCOLOR*[desc.Height];
	for ( i = 0 ; i < desc.Height ; ++i)
		pColor[i] = new D3DCOLOR[desc.Width];

	//Lock entire texture to read pixel
	hr = m_MapTex->LockRect( 0 , &rect , NULL , D3DLOCK_READONLY );
	if(FAILED(hr))
		return ;

	BYTE* pBits = (BYTE*)rect.pBits;

	for (i = 0 ; i < desc.Height ; ++i)
	{
		for ( j = 0 ; j < desc.Width ; ++j)
		{
			DWORD index =( j*4 + ( i * (rect.Pitch) ));

			// Blue
			BYTE b = pBits[index];

			// Green
			BYTE g = pBits[index+1];

			// Red
			BYTE r = pBits[index+2];

			// Alpha
			BYTE a = pBits[index+3];
			D3DCOLOR color = D3DCOLOR_ARGB(a , r , g , b );
			pColor[i][j] = color;
		}
	}
	//Unlock texture
	m_MapTex->UnlockRect(0);

	
	m_Terrain=new int*[m_Width];
	for(int i=0;i<m_Width;i++)
	{
		m_Terrain[i]=new int[m_Height];
	}
	for (int i =0 ; i< m_Width; i++)	{
		for (int j = 0 ; j<m_Height; j++)	{			 
			m_Terrain[i][j] = 0;
		}
	}



	m_TerrainExtends=new int*[m_Width];
	for(int i=0;i<m_Width;i++)
	{
		m_TerrainExtends[i]=new int[m_Height];
	}


	for (int i =0 ; i< m_Width; i++)	{
		for (int j = 0 ; j<m_Height; j++)	{			 
			m_TerrainExtends[i][j] = 0;
		}
	}


	for (i = 0 ; i < m_Width ; ++i)
	{
		for ( j = 0 ; j < m_Height ; ++j)
		{
			D3DCOLOR color = (pColor[j][i]);
			int r = (color&0x00ff0000) >> 16;

			if(r>=200 && r<=204)
			{
				m_Terrain[i][j] = 1;
			}
			if(r>=200 && r<=214)
			{
				m_TerrainExtends[i][j] = r;
			}
			if(r>=220 && r<=224)
			{
				m_Terrain[i][j] = 1;
			}
			if(r>=220 && r<=234)
			{
				m_TerrainExtends[i][j] = r;
			}
			if (r == 1)
			{
				GodLike_Beast* _GodLike = new GodLike_Beast() ;
				_GodLike->setXY(i*50,j*50-460);
				ManagerObject::Instance()->getListBoss()->push_back(_GodLike);
			}
			if (r==10)
			{
				Monster* _Monster = new Monster();
				_Monster->setXY(i*50,j*50-60);
				ManagerObject::Instance()->getQuadTree()->Insert(_Monster);
			}
		}
	}
}