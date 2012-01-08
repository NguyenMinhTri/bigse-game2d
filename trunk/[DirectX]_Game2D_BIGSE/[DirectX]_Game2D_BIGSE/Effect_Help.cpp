#include "Effect_Help.h"


Effect_Help::Effect_Help(LPDIRECT3DDEVICE9 m_Device)
{
	m_Effect=new Sprite(m_Device,"data\\image\\EffectHelp.png",16,17,1);
	m_InfoEffect.setXY(rand()%1024,rand()%720);
	m_timeLife=0;
	m_Old=(rand()%10)*0.5;
}

void Effect_Help::Repress()
{
	m_InfoEffect.setXY(rand()%1024,rand()%720);
	m_timeLife=0;
	m_Old=(rand()%10)*0.5;
	m_InfoEffect.setColorAlpha(1);
}
Effect_Help::~Effect_Help(void)
{
}
