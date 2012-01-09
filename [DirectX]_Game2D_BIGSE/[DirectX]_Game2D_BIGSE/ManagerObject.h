#pragma once
#include <vector>
#include "MyObject.h"
#include "EffectSystem.h"
#include "QuadTree.h"
#include "Terrain.h"
using namespace std;

class ManagerObject
{
private:
	static ManagerObject* m_Instance;
	std::vector<MyObject*> *m_ListItem;
	std::vector<MyObject*> *m_ObjectsCamera;
	std::vector<MyObject*> *m_ListMonster ;
	std::vector<MyObject*> *m_ListBoss ;
	std::vector<MyObject*> *m_SpecialObject ;
	std::vector<EffectSystem*> *m_ListEffect ;
	float m_Time;
	QuadTree* m_QuadTree;

	Terrain* m_Map;
	ManagerObject(void);
public:
	
	~ManagerObject(void);
	static ManagerObject* Instance()
	{
		if (m_Instance==NULL)
		{
			m_Instance = new ManagerObject();
		}
		return m_Instance;
	}

	std::vector<MyObject*>* getListBoss  () 
	{
		return m_ListBoss;
	}
	std::vector<MyObject*>* getObjectCamera() 
	{
		return m_ObjectsCamera;
	}

	void setListBoss  (std::vector<MyObject*> *_ListBoss)
	{
		m_ListBoss = _ListBoss;
	}
	void setMap (Terrain* _Map)
	{
		m_Map = _Map;
	}
	void setTime  (float _Time)
	{
		m_Time = _Time;
	}
	int getTime ()
	{
		return m_Time;
	}
	Terrain* getMap() 
	{
		return m_Map;
	}
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	void setQuadTree (QuadTree* _QuadTree)
	{
		m_QuadTree = _QuadTree;
	}

	QuadTree* getQuadTree () 
	{
		return m_QuadTree;
	}


	void setListEffect(std::vector<EffectSystem*> *_ListEffect)
	{
		m_ListEffect = _ListEffect;
	}

	std::vector<EffectSystem*>* getListEffect () 
	{
		return m_ListEffect;
	}

	std::vector<MyObject*>* getListMonster  () 
	{
		return m_ListMonster;
	}

	void setListMonster  (std::vector<MyObject*> *_ListMonster)
	{
		m_ListMonster = _ListMonster;
	}

	void setListObject (std::vector<MyObject*> *_ListObject)
	{
		m_ListItem = _ListObject;
	}

	std::vector<MyObject*>* getListItem () 
	{
		return m_ListItem;
	}

	void setObjects (std::vector<MyObject*> *_Object)
	{
		m_ObjectsCamera = _Object;
	}

	std::vector<MyObject*>* getObjects () 
	{
		return m_ObjectsCamera;
	}

	void setSpecialObjects (std::vector<MyObject*> *_Object)
	{
		m_SpecialObject = _Object;
	}

	std::vector<MyObject*>* getSpecialObjects () 
	{
		return m_SpecialObject;
	}
};

