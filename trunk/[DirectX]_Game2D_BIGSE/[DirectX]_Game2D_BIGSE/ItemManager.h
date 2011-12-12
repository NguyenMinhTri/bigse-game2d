#pragma once
#include <vector>
#include <stdlib.h>
#include "Item.h"
using namespace std;
class ItemManager
{
protected:
	std::vector<Item*> m_List;

public:
	ItemManager(void);
	~ItemManager(void);

	void AddItem (Item* _Item);
	void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	void ProcessCollision (MyObject* _Obj);
	bool ActiveItem (int _Index,float _X,float _Y);
	void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler,float x, float y);

	Item* getItem (int _Index)
	{
		return m_List[_Index];
	}
};

