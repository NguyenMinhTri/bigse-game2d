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
using namespace std;
class State_Play :
	public iState
{

	std::vector<MyObject*> *m_ListItem;
	std::vector<MyObject*> *m_ObjectsCamera;
	std::vector<EffectSystem*> *m_ListEffect;
	std::vector<MyObject*> *m_ListMonster ;
	std::vector<MyObject*> *m_ListBoss ;

	int m_STT ;
	QuadTree* m_QuadTree;

	Item *m_Item;
	Character* m_Monster ;
	Character* m_char;
    Archer *m_Archer; 
	Angle *m_Angle ;

	Monster* m_Monster1;
	Monster* m_Monster2;
	Magician* m_Magician;

	SnakeMans* m_SnakeMan;
	GodLike_Beast* m_GodLike ;
	Hero* m_Hero;

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
