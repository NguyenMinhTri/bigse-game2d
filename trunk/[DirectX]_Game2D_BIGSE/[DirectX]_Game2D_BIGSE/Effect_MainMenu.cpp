#include "Effect_MainMenu.h"


Effect_MainMenu::Effect_MainMenu(LPDIRECT3DDEVICE9 m_Device)
{
	m_Effect=new Sprite(m_Device,"data\\image\\MainMenuEffect.png",25,25,1);
	m_InfoEffect.setSize(25,25);
	m_InfoEffect.setXY(rand()%1024,rand()%720);
	m_InfoEffect.setCurFrame(0);
	float i=0.1*(rand()%10)+0.5;
	m_InfoEffect.setScaleXY(i,i);
	m_timeLife=0;
	m_Old=rand()%10;
	m_Old=0.1*m_Old+0.5;
}


Effect_MainMenu::~Effect_MainMenu(void)
{
}
