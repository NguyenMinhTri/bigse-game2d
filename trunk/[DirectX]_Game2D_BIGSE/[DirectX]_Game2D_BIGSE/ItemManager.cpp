#include "ItemManager.h"

ItemManager::ItemManager(void)
{
}


ItemManager::~ItemManager(void)
{
}
void ItemManager :: AddItem(Item *_Item)
{
	m_List.push_back(_Item);
}

void ItemManager::ProcessCollision(MyObject* _Obj)
{
	for(int i=0;i<m_List.size();i++)
	{
// 		if (m_List[i]->getSTT() != ACTIVE)
// 		{
// 			continue;
// 		}
	    m_List[i]->ProcessCollision(_Obj);
	}
}

void ItemManager ::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler,float x, float y)
{
	for(int i=0;i<m_List.size();i++)
	{
// 		if (m_List[i]->getSTT() != ACTIVE)
// 		{
// 			continue;
// 		}
		m_List[i]->Draw(_MWorld,_Handler,x, y);
	}
}