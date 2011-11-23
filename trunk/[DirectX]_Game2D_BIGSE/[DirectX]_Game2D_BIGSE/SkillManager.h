#pragma once
#include <list>
#include <stdlib.h>
#include "Skill.h"
using namespace std;
/*
Iterator skill
*/
typedef list<Skill*>::const_iterator siter;
class SkillManager
{
protected:
	std::list<Skill*> m_List;
public:
	SkillManager(void);
	~SkillManager(void);
	int Count ();
	void AddSkill (Skill* _skill);

	void ProcessCollision (MyObject* _Obj);
	bool ActiveSkill ();

};

