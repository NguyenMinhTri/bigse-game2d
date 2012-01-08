#include "Effect_Setting.h"


Effect_Setting::Effect_Setting(LPDIRECT3DDEVICE9 m_Device)
{
	m_Effect=new Sprite(m_Device,"data\\image\\Setting_Effect.png",13,15,1);
	m_InfoEffect.setXY(rand()%1024,rand()%720);
	m_timeLife=0;
	m_Old=(rand()%10)*0.5;
}

void Effect_Setting::Repress()
{
	m_InfoEffect.setXY(rand()%1024,rand()%720);
	m_timeLife=0;
	m_Old=(rand()%10)*0.5;
	m_InfoEffect.setColorAlpha(1);
}
Effect_Setting::~Effect_Setting(void)
{
}
