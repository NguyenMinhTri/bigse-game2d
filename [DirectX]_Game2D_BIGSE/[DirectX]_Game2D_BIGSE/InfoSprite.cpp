#include "InfoSprite.h"


InfoSprite::InfoSprite(void)
{
	m_X			= 0;
	m_Y			= 0;
	m_Width		= 0;
	m_Height	= 0;
	m_Depth		= 0.5f;
	m_CurFrame	= 0;
	m_ScaleX	= 1.0f;
	m_ScaleY	= 1.0f;
	m_Rotation	= 0.0f;
	m_Color		= D3DXCOLOR(1,1,1,1);
}


InfoSprite::~InfoSprite(void)
{
}

