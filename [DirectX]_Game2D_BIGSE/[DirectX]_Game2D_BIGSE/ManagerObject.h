#pragma once
#include <vector>
#include "MyObject.h"
using namespace std;

class ManagerObject
{
private:
	static ManagerObject* m_Instance;
	std::vector<MyObject*> *m_ListItem;
	std::vector<MyObject*> *m_ObjectsCamera;
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

