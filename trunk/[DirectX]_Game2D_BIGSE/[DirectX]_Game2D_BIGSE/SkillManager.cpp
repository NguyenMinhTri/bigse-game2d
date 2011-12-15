#include "SkillManager.h"
#include "Global.h"


SkillManager::SkillManager(void)
{
	
}


SkillManager::~SkillManager(void)
{
}

void SkillManager ::AddSkill(Skill *_skill)
{
	m_List.push_back(_skill);
}
void SkillManager :: ProcessCollision(MyObject*_Obj)
{
	for (int i =0; i < m_List.size(); i++)
	{
		if (m_List[i]->getSTT() != ACTIVE|| // Skill chua dc kich hoat		
			m_List[i]->getiCollision() == false || // Skill chua bat dau tinh va cham
			m_List[i]->getRect().iCollision(_Obj->getRect())==false) // Chua co va cham
		{
			continue;
		}
		
		m_List[i]->ProcessCollision(_Obj);
	}

}
bool SkillManager :: ActiveSkill (int _Index,float _X,float _Y,int _Dir)
{
	m_List[_Index]->Active(_X,_Y,_Dir);
	return true ;
}
void SkillManager ::Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	for (int i =0; i < m_List.size(); i++)
	{		
		m_List[i]->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
}
void SkillManager :: Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	for (int i =0; i < m_List.size(); i++)
	{
		if (m_List[i]->getSTT() != ACTIVE)
		{
			continue;
		}
		m_List[i]->Draw(_MWorld,_Handler);
	}
}
