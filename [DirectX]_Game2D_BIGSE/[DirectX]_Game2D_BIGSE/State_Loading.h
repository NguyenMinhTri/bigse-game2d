#pragma once
#include "istate.h"
#include "Sprite.h"
#include <vector>
#include "QuadTree.h"
#include "MyObject.h"
#include "EffectSystem.h"
#include "LoadMap.h"
#include "Terrain.h"

using namespace std;
class State_Loading :
	public iState
{
	int m_Percent;
	int m_IDHero;
	Sprite* m_Loading1;
	Sprite* m_Loading3;
	Sprite* m_Loading2;
	LPDIRECT3DTEXTURE9 m_Tex;
	LPD3DXSPRITE m_Handle;
	RECT rect;

	std::vector<MyObject*> *m_ListItem;
	std::vector<MyObject*> *m_ObjectsCamera;
	std::vector<EffectSystem*> *m_ListEffect;
	std::vector<MyObject*> *m_ListMonster ;
	std::vector<MyObject*> *m_ListBoss ;
	std::vector<MyObject*> *m_SpecialObject ;

	QuadTree* m_QuadTree;
	LoadMap* m_LoadMap;
	Terrain* m_Map;
	LPCTSTR m_fileMap;
public:
	State_Loading(iPlay* GamePlay,LPCTSTR _fileMap,int _IDHero);
	~State_Loading(void);
	void IsKeyDown(int KeyCode);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
};

