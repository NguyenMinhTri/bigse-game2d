#pragma once
#include "istate.h"
#include "Character.h"
#include "Terrain.h"
#include "Camera.h"
#include "Monster.h"
#include "Archer.h"
#include "Magician.h"
#include "Angle.h"
#include <vector>
#include "EffectSystem.h"
#include "QuadTree.h"
#include "GodLike_Beast.h"
#include "EffectSystem.h"
#include "SnakeMans.h"
#include "Hero.h"
#include "LoadMap.h"
#include "Monster.h"
using namespace std;
class State_Play :
	public iState
{
	LoadMap* m_LoadMap;

	std::vector<MyObject*> *m_ListItem;
	std::vector<MyObject*> *m_ObjectsCamera;
	std::vector<EffectSystem*> *m_ListEffect;
	std::vector<MyObject*> *m_ListMonster ;
	std::vector<MyObject*> *m_ListBoss ;

	int m_STT ;
	QuadTree* m_QuadTree;

	Item *m_Item;	
	Hero* m_Hero;
	SnakeMans* m_SnakeMans;
	LPD3DXSPRITE m_Handle;
	Terrain* m_Map;
	Camera* m_Camera;
	D3DXMATRIX m_mtWorld;
public:
	State_Play(iPlay* GamePlay);
	~State_Play(void);
	void IsKeyDown(int KeyCode);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Init();
	void Update(float _Time);
	void Draw();
	void Release();
};

