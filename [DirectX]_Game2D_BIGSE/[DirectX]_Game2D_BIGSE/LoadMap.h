#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class LoadMap
{
public:
	LPDIRECT3DTEXTURE9 m_MapTex;
	int m_Width, m_Height;
	int **m_Terrain ;
	int **m_TerrainExtends ;
	LoadMap(void);
	~LoadMap(void);
	HRESULT LoadMapFormFile (LPCTSTR _file, LPDIRECT3DDEVICE9 _Device);

	void TranslateMap ();
};

