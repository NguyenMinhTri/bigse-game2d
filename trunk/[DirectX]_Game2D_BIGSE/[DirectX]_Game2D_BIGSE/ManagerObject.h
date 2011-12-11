#pragma once
#include <vector>
#include "MyObject.h"
using namespace std;

class ManagerObject
{
private:
	static ManagerObject* m_Instance;
	std::vector<MyObject*> *m_ListObject;
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
		m_ListObject = _ListObject;
	}
	std::vector<MyObject*>* getListObject () 
	{
		return m_ListObject;
	}

};

