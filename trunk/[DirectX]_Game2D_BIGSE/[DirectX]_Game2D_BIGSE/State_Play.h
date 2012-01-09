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
#include "EffectFont.h"
using namespace std;
class State_Play :
	public iState
{
	LoadMap* m_LoadMap;
	EffectFont* m_NumTime;
	std::vector<MyObject*> *m_ListItem;
	std::vector<MyObject*> *m_ObjectsCamera;
	std::vector<EffectSystem*> *m_ListEffect;
	std::vector<MyObject*> *m_ListMonster ;
	std::vector<MyObject*> *m_ListBoss ;
	std::vector<MyObject*> *m_SpecialObject ;

	int m_Flag;// 1=Pause | 2=Effect | 3=TimeOver | 4=Lose | 5=Win
	float m_Time;
	float m_FlagAni;
	Sprite* m_sWin;
	Sprite* m_sLose;
	Sprite* m_sStart;
	Sprite* m_sTime;
	Sprite* m_bar;
	Sprite* m_barheath;
	InfoSprite m_infoFlag;

	int m_STT ;
	QuadTree* m_QuadTree;

	Item *m_Item;	
	Character* m_Hero;
	
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

