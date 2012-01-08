#include "Effect_MainMenu.h"


Effect_MainMenu::Effect_MainMenu(LPDIRECT3DDEVICE9 m_Device)
{
	m_Effect=new Sprite(m_Device,"data\\image\\MainMenuEffect.png",25,25,1);
	m_InfoEffect.setXY(rand()%1024,-100+rand()%820);
	float i=0.1*(rand()%10)+0.5;
	m_InfoEffect.setScaleXY(i,i);
}

void Effect_MainMenu::Repress()
{
	m_InfoEffect.setXY(rand()%1024,-rand()%720);
	float i=0.1*(rand()%10)+0.5;
	m_InfoEffect.setScaleXY(i,i);

}
Effect_MainMenu::~Effect_MainMenu(void)
{
}
