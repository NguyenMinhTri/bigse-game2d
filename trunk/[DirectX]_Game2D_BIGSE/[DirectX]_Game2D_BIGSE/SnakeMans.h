#pragma once
#include "character.h"
#include "RSMainGame.h"
#include "Arrow.h"
class SnakeMans :
	public Character
{
public:

	virtual void Init();
	virtual void Animation(float _Time);
	SnakeMans(void);
	~SnakeMans(void);

};

