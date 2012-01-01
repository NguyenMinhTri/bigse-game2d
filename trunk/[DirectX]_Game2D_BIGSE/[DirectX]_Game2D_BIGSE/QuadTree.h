#pragma once
#include "QuadTreeNode.h"
#include "MyObject.h"
class QuadTree
{
public:
	QuadTreeNode m_Root;
	CRECT m_Bounds;
	QuadTree(CRECT _Bounds);
	~QuadTree(void);
	int Count ()
	{
		return m_Root.Count();
	}

	void Insert (MyObject* _Obj);

	std::vector<MyObject*>* Query (CRECT _Area);

};

