#include "RECT.h"
#include <math.h>


CRECT::CRECT(void)
{
	Left	= 0;
	Right	= 0;
	Top		= 0;
	Bottom	= 0;
}
CRECT::CRECT(float _left,float _right,float _top,float _bottom)
{
	Left	= _left;
	Right	= _right;
	Top		= _top;
	Bottom	= _bottom;
}

CRECT::~CRECT(void)
{
}

bool CRECT::iCollision(CRECT _Rect)
{
	float dh = (fabs(Top-_Rect.Bottom)>fabs((Bottom-_Rect.Top))) ? fabs(Top-_Rect.Bottom) : fabs((Bottom-_Rect.Top));
	float dw = (fabs(Left - _Rect.Right) > fabs(Right - _Rect.Left)) ? fabs(Left-_Rect.Right) : fabs(Right - _Rect.Left);

	return ((dw < ((Right-Left)+(_Rect.Right-_Rect.Left)))&&
		(dh < ((Bottom-Top) + (_Rect.Bottom- _Rect.Top))));
}