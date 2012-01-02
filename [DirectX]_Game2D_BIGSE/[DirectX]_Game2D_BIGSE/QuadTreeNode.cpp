#include "QuadTreeNode.h"


QuadTreeNode::QuadTreeNode()
{
	m_Contents = new std::vector<MyObject*>();
	m_Child = NULL;
}
QuadTreeNode::~QuadTreeNode(void)
{
	if (m_Child!=NULL)
	{
		delete m_Child;
	}
	if (m_Contents!=NULL)
	{
		delete m_Contents;
	}
}
std::vector<MyObject*>* QuadTreeNode::Contents()
{
	std::vector<MyObject*> *result = new std::vector<MyObject*>();
	result->insert(result->begin(),m_Contents->begin(),m_Contents->end());
	m_Contents->clear();
	return result;

}
int QuadTreeNode::Count()
{
	int result =0;
	result+= m_Contents->size();
	if (m_Child!=NULL)
	{
		for (int i=0;i <4;i++)
		{
			result += m_Child[i].Count();
		}
	}
	return result;
}

bool QuadTreeNode::iEmpty()
{
	if (this->Count()>0)
	{
		return false;
	}
	/*if (m_Child!=NULL)
	{
		/ *delete[] m_Child;
		m_Child = NULL;* /
	}*/
	return true;	
}

std::vector<MyObject*>* QuadTreeNode::SubTreeContents()
{
	std::vector<MyObject*> *result = new std::vector<MyObject*>();
	std::vector<MyObject*> *Contents = this->Contents(); 
	delete Contents;
	result->insert(result->begin(),Contents->begin(),Contents->end());

	if (m_Child!=NULL)
	{
		for (int i =0;i<4;i++)
		{
			std::vector<MyObject*> *SubTreeContents = m_Child[i].SubTreeContents();
			result->insert(result->begin(),SubTreeContents->begin(),SubTreeContents->end());
			delete SubTreeContents;
		}
	}
	return result;
}

void QuadTreeNode::CreateSubNodes()
{
	 // the smallest subnode has an area 
	if (m_Bounds.Right-m_Bounds.Left<100)
	{
		return;
	}
	if (m_Bounds.Bottom-m_Bounds.Top<100)
	{
		return;
	}

	float halfWidth = (m_Bounds.Right-m_Bounds.Left)/2;
	float halfHeight = (m_Bounds.Bottom-m_Bounds.Top)/2;

	m_Child = new QuadTreeNode[4]();

	m_Child[0].setBounds(CRECT(m_Bounds.Left,m_Bounds.Left+halfWidth,
		m_Bounds.Top,m_Bounds.Top+halfHeight));
	m_Child[1].setBounds(CRECT(m_Bounds.Left+halfWidth,m_Bounds.Right,
		m_Bounds.Top,m_Bounds.Top+halfHeight));
	m_Child[2].setBounds(CRECT(m_Bounds.Left,m_Bounds.Left+halfWidth,
		m_Bounds.Top+halfHeight,m_Bounds.Bottom));
	m_Child[3].setBounds(CRECT(m_Bounds.Left+halfWidth,m_Bounds.Right,
		m_Bounds.Top+halfHeight,m_Bounds.Bottom));
}
void QuadTreeNode::Insert(MyObject* _Obj)
{
	if (!m_Bounds.iContains(_Obj->getRect()))
	{
		return;
	}
	if (m_Child==NULL)
	{
		CreateSubNodes();
	}
	if (m_Child!=NULL)
	{
		for (int i =0;i<4;i++)
		{
			if (m_Child[i].m_Bounds.iContains(_Obj->getRect()))
			{
				m_Child[i].Insert(_Obj);
				return;
			}
		}
	}
	this->m_Contents->push_back(_Obj);
}

std::vector<MyObject*>* QuadTreeNode::Query (CRECT _Area)
{
	std::vector<MyObject*> *result = new std::vector<MyObject*>();

	for (std::vector<MyObject*>::iterator i = m_Contents->begin(); i != m_Contents->end(); )
	{
		if (_Area.iCollision((*i)->getRect()))
		{
			result->push_back((*i));

			i= m_Contents->erase(i);
		} 
		else
		{
			i++;
		}
	}

	if (m_Child!=NULL)
	{
		for (int i =0 ; i<4;i++)
		{
			if (m_Child[i].iEmpty())
			{
				continue;
			}
			if (m_Child[i].m_Bounds.iContains(_Area))
			{
				std::vector<MyObject*> *Query = m_Child[i].Query(_Area);
				result->insert(result->begin(),Query->begin(),Query->end());
				delete Query;
				break;
			}
			if (_Area.iContains(m_Child[i].m_Bounds))
			{
				std::vector<MyObject*> *Query = m_Child[i].SubTreeContents();
				result->insert(result->begin(),Query->begin(),Query->end());
				delete Query;
			}
			if (m_Child[i].m_Bounds.iCollision(_Area))
			{
				std::vector<MyObject*> *Query = m_Child[i].Query(_Area);
				result->insert(result->begin(),Query->begin(),Query->end());
				delete Query;
			}
		}
	}

	return result;
}
