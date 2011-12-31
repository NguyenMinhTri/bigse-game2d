#pragma once
#include <vector>
#include "MyObject.h"
#include "EffectSystem.h"
using namespace std;

class ManagerObject
{
private:
	static ManagerObject* m_Instance;
	std::vector<MyObject*> *m_ListItem;
	std::vector<MyObject*> *m_ObjectsCamera;
	std::vector<MyObject*> *m_ListMonster ;
	std::vector<MyObject*> *m_ListBoss ;

	std::vector<EffectSystem*> *m_ListEffect ;
	
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

	void setListBoss  (std::vector<MyObject*> *_ListBoss)
	{
		m_ListBoss = _ListBoss;
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
};

