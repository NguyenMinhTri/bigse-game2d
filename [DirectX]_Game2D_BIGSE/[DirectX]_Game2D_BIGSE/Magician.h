#pragma once
#include "character.h"
class Magician :
	public Character
{
public:
	Magician(void);
	~Magician(void);
	virtual void Init () ;
	virtual void Animation (float _Time) ;
};

