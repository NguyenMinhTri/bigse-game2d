#include "QuadTree.h"


QuadTree::QuadTree(CRECT _Bounds)
{
	m_Bounds = _Bounds;
	m_Root.m_Bounds = _Bounds;
}


QuadTree::~QuadTree(void)
{
}
void QuadTree::Insert (MyObject* _Obj)
{
	m_Root.Insert(_Obj);
}
std::vector<MyObject*>* QuadTree::Query (CRECT _Area)
{
	return m_Root.Query(_Area);
}
