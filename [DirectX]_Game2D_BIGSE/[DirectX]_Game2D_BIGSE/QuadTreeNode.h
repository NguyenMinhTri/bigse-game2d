#pragma once
#include "MyObject.h"
#include <vector>
class QuadTreeNode
{
	std::vector<MyObject*> *m_Contents;
	
	QuadTreeNode* m_Child;
public:
	CRECT m_Bounds;
	QuadTreeNode();
	~QuadTreeNode(void);

	// remove and get all object in node  
	std::vector<MyObject*>* Contents();

	void setBounds (CRECT _Bounds)
	{
		m_Bounds = _Bounds;
	}

	CRECT getBounds ()
	{
		return m_Bounds;
	}

	// get count object in node and child
	int Count ();

	bool iEmpty ();

	// remove and get all object in node  child
	std::vector<MyObject*>* SubTreeContents();

	void CreateSubNodes ();

	void Insert (MyObject* _Obj);

	std::vector<MyObject*>* Query (CRECT _Area);

};

