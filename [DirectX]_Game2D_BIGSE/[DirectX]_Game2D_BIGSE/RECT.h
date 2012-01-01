#pragma once
class CRECT
{
public:
	float Top,Left,Right,Bottom;
	CRECT(void);
	CRECT(float _left,float _right,float _top,float _bottom);
	~CRECT(void);
	bool iCollision (CRECT _Rect);
	bool iContains (CRECT _Rect);
};

