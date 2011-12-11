#pragma once
#include <vector>
#include <stdlib.h>
#include "Skill.h"
using namespace std;

class SkillManager
{
protected:
	std::vector<Skill*> m_List;
	
public:
	SkillManager(void);
	~SkillManager(void);

	void AddSkill (Skill* _skill);
	void Update (float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight);
	void ProcessCollision (MyObject* _Obj);
	bool ActiveSkill (int _Index,float _X,float _Y,int _Dir);
	void Draw (D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler);

	Skill* getSkill (int _Index)
	{
		return m_List[_Index];
	}

};

