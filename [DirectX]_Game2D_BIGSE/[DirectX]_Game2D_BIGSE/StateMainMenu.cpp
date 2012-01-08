#include "StateMainMenu.h"
#include "StatePlayer.h"
#include "SoundGame.h"
#include "State_Play.h"
#include "StateHelp.h"
#include "State_Setting.h"

StateMainMenu::StateMainMenu(iPlay* GamePlay): iState(GamePlay)
{
	test=false;
	m_ID=MAINMENU;
	Init();
	test=true;
}


StateMainMenu::~StateMainMenu(void)
{
}
void StateMainMenu::Init()
{
/*	SoundGame::Instance()->PlayBackGame();*/
	D3DXCreateSprite(m_Device,&m_Handle);
	CoAlMain=0;
	CoAlLogo=1;
	m_DirectOfMain=1;
	m_AnTime=0;
	m_MainMenu = new Sprite(m_Device,"data\\image\\MainMenu.png",1024,720,1);
	m_Logo=new Sprite(m_Device,"data\\image\\LogoMainMenu.png",630,230,1);
	m_Bird1=new Sprite(m_Device,"data\\image\\Pet_Hero_Move.png",126,170,10);
	m_Bird2=new Sprite(m_Device,"data\\image\\Pet_Hero_Move.png",126,170,10);

	m_ButtonStart=new Sprite(m_Device,"data\\image\\Button_Start.png",174,49,1);
	m_ButtonSetting=new Sprite(m_Device,"data\\image\\Button_Setting.png",117,51,1);
	m_ButtonHelp=new Sprite(m_Device,"data\\image\\Button_Help.png",74,51,1);
	m_ButtonExit=new Sprite(m_Device,"data\\image\\Button_Exit.png",74,36,1);
	m_listEffect=new vector<Effect_MainMenu*>();
	m_listHoldButton=new vector<Sprite*>();
	m_listInfoHoldButton = new vector<InfoSprite>();
	m_CountOfEffect=50;
	for(int i=0;i<4;i++)
	{
		Sprite* m_HoldMainMenu;
		m_HoldMainMenu=new Sprite(m_Device,"data\\image\\Hold_Button.png",360,160,14);
		m_listHoldButton->push_back(m_HoldMainMenu);

		InfoSprite m_InfoHoldButton;
		m_InfoHoldButton.setSize(360,160);
		m_InfoHoldButton.setXY(360,260+i*80);
		m_InfoHoldButton.setCurFrame(0);
		m_InfoHoldButton.setDepth(0.6f);
		m_listInfoHoldButton->push_back(m_InfoHoldButton);
	}

	for(int i=0;i<m_CountOfEffect;i++)
	{
		Effect_MainMenu *temp=new Effect_MainMenu(m_Device);
		m_listEffect->push_back(temp);

	}
	m_TimeToUpCount=0;
	m_InfoMainMenu.setXY(0,0);
	m_InfoMainMenu.setSize(1024,720);
	m_InfoMainMenu.setDepth(0.5);
	m_InfoMainMenu.setCurFrame(0);

	m_InfoLogo.setSize(630,230);
	m_InfoLogo.setXY(210,0);
	m_InfoLogo.setDepth(0.6f);

	m_InfoButtonStart.setSize(174,49);
	m_InfoButtonStart.setXY(450,323);
	m_InfoButtonStart.setDepth(0.3f);

	m_InfoButtonSetting.setSize(117,51);
	m_InfoButtonSetting.setXY(487,405);
	m_InfoButtonSetting.setDepth(0.3f);

	m_InfoButtonHelp.setSize(74,51);
	m_InfoButtonHelp.setXY(500,486);
	m_InfoButtonHelp.setDepth(0.3f);

	m_InfoButtonExit.setSize(74,36);
	m_InfoButtonExit.setXY(500,565);
	m_InfoButtonExit.setDepth(0.3f);
	
	m_InfoBird1.setCurFrame(0);
	m_InfoBird2.setCurFrame(0);
	m_InfoBird2.setSize(16,170);
	m_InfoBird1.setSize(16,170);
	m_InfoBird1.setXY(-100,200);
	m_InfoBird2.setXY(1164,200);
	m_InfoBird1.setScaleX(-1);
	m_InfoBird2.setScaleX(1);
}
void StateMainMenu ::ProcessMouse(DIMOUSESTATE MouseState,POINT Positon)
{
		if(Positon.x >m_InfoButtonStart.getX() && Positon.x <=m_InfoButtonStart.getX()+m_InfoButtonStart.m_Width
			&&Positon.y >= m_InfoButtonStart.getY()-30 && Positon.y <=m_InfoButtonStart.getY()+m_InfoButtonStart.m_Height)
		{
			m_InfoButtonStart.setScaleXY(1.1f,1.1f);		
		}
		else
			m_InfoButtonStart.setScaleXY(1,1);
		
		if(Positon.x >m_InfoButtonSetting.getX() && Positon.x <=m_InfoButtonSetting.getX()+m_InfoButtonSetting.m_Width
			&&Positon.y >= m_InfoButtonSetting.getY()-30 && Positon.y <=m_InfoButtonSetting.getY()+m_InfoButtonSetting.m_Height)
		{
			m_InfoButtonSetting.setScaleXY(1.2f,1.2f);		
		}
		else
			m_InfoButtonSetting.setScaleXY(1,1);
		if(Positon.x >m_InfoButtonHelp.getX() && Positon.x <=m_InfoButtonHelp.getX()+m_InfoButtonHelp.m_Width
			&&Positon.y >= m_InfoButtonHelp.getY()-30 && Positon.y <=m_InfoButtonHelp.getY()+m_InfoButtonHelp.m_Height)
		{
			m_InfoButtonHelp.setScaleXY(1.2f,1.2f);		
		}
		else
			m_InfoButtonHelp.setScaleXY(1,1);
		if(Positon.x >m_InfoButtonExit.getX() && Positon.x <=m_InfoButtonExit.getX()+m_InfoButtonExit.m_Width
			&&Positon.y >= m_InfoButtonExit.getY()-30 && Positon.y <=m_InfoButtonExit.getY()+m_InfoButtonExit.m_Height)
		{
			m_InfoButtonExit.setScaleXY(1.2f,1.2f);		
		}
		else
			m_InfoButtonExit.setScaleXY(1,1);
		////////////////////////////
		if(MouseState.rgbButtons[0])
		{
			if(Positon.x >m_InfoButtonStart.getX() && Positon.x <=m_InfoButtonStart.getX()+m_InfoButtonStart.m_Width
				&&Positon.y >= m_InfoButtonStart.getY()-20 && Positon.y <=m_InfoButtonStart.getY()+m_InfoButtonStart.m_Height)
			{
				m_InfoButtonStart.setScaleXY(0.9f,0.9f);	
				m_iPlay->SetNextState(new StatePlayer(m_iPlay));
			}
			else
				m_InfoButtonStart.setScaleXY(1,1);
			if(Positon.x >m_InfoButtonSetting.getX() && Positon.x <=m_InfoButtonSetting.getX()+m_InfoButtonSetting.m_Width
				&&Positon.y >= m_InfoButtonSetting.getY()-20 && Positon.y <=m_InfoButtonSetting.getY()+m_InfoButtonSetting.m_Height)
			{
				m_InfoButtonSetting.setScaleXY(0.9f,0.9f);	
				m_iPlay->SetNextState(new StateSetting(m_iPlay));
			}
			else
				m_InfoButtonSetting.setScaleXY(1,1);
			if(Positon.x >m_InfoButtonHelp.getX() && Positon.x <=m_InfoButtonHelp.getX()+m_InfoButtonHelp.m_Width
				&&Positon.y >= m_InfoButtonHelp.getY()-20 && Positon.y <=m_InfoButtonHelp.getY()+m_InfoButtonHelp.m_Height)
			{
				m_InfoButtonHelp.setScaleXY(0.9f,0.9f);		
				m_iPlay->SetNextState(new StateHelp(this->m_iPlay));
			}
			else
				m_InfoButtonHelp.setScaleXY(1,1);
			if(Positon.x >m_InfoButtonExit.getX() && Positon.x <=m_InfoButtonExit.getX()+m_InfoButtonExit.m_Width
				&&Positon.y >= m_InfoButtonExit.getY()-20 && Positon.y <=m_InfoButtonExit.getY()+m_InfoButtonExit.m_Height)
			{
				m_InfoButtonExit.setScaleXY(0.9f,0.9f);		
			}
			else
				m_InfoButtonExit.setScaleXY(1,1);
		}
		/////////////////////////////
}
void StateMainMenu ::Update(float _Time)
{

	if(test==false)
	{
		return;
	}
	m_TimeToUpCount+=_Time;
	if(m_TimeToUpCount>=0.1)
	{
		m_TimeToUpCount=0;
		for (std::vector<Effect_MainMenu*>::iterator i = m_listEffect->begin();i<m_listEffect->end();i++)
		{	
			if((*i)->m_InfoEffect.getY()>=720)
			{
				(*i)->Repress();
			}
			(*i)->m_InfoEffect.setY((*i)->m_InfoEffect.getY()+2);
			int vx=5-rand()%10;
			(*i)->m_InfoEffect.setX((*i)->m_InfoEffect.getX()+vx);
		}
	}
	
	
	if(CoAlMain<=1)
	{
		CoAlMain+=_Time/4;
		m_InfoMainMenu.setColorAlpha(CoAlMain);
		m_InfoLogo.setColorAlpha(CoAlMain);
		for(int i=0;i<4;i++)
		{
			m_listInfoHoldButton->at(i).setCurFrame(10);
			m_listInfoHoldButton->at(i).setColorAlpha(CoAlMain);
		}
	}
	else
	{
		if(m_InfoBird1.getX()<=320)
		{
			m_InfoBird1.setX(m_InfoBird1.getX()+_Time*150);
			m_InfoBird2.setX(m_InfoBird2.getX()-_Time*150);
		}
		m_AnTime+=_Time;
		if(m_AnTime>=0.15)
		{
			
			m_AnTime-=0.15;
			for(int i=0;i<4;i++)
			{
				m_listInfoHoldButton->at(i).NextFrame(0,11);
				if(m_listInfoHoldButton->at(i).getCurFrame()>=10)
					m_listInfoHoldButton->at(i).setCurFrame(0);
			}
			m_InfoBird1.NextFrame(0,6);
			if(m_InfoBird1.getCurFrame()>=5)
				m_InfoBird1.setCurFrame(0);
			m_InfoBird2.NextFrame(0,6);
			if(m_InfoBird2.getCurFrame()>=5)
				m_InfoBird2.setCurFrame(0);
		}
		if(CoAlLogo>=1)
			m_DirectOfMain=-1;
		if(CoAlLogo<=0.3)
			m_DirectOfMain=1;
		CoAlLogo=CoAlLogo+m_DirectOfMain*_Time;
		m_InfoLogo.setColorAlpha(CoAlLogo);
	}

}
void StateMainMenu ::Draw()
{
	if(test==false)
		return;
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(71,168,208),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);
		m_MainMenu->Draw(m_InfoMainMenu,m_Handle);
		m_Logo->Draw(m_InfoLogo,m_Handle);
		for(int i=0;i<m_listHoldButton->size();i++)
		{
			Sprite* temp=m_listHoldButton->at(i);
			InfoSprite tempif=m_listInfoHoldButton->at(i);
			temp->Draw(tempif,m_Handle);
		}
		m_ButtonStart->Draw(m_InfoButtonStart,m_Handle);
		m_ButtonSetting->Draw(m_InfoButtonSetting,m_Handle);
		m_ButtonHelp->Draw(m_InfoButtonHelp,m_Handle);
		m_ButtonExit->Draw(m_InfoButtonExit,m_Handle);
		m_Bird1->Draw(m_InfoBird1,m_Handle);
		m_Bird2->Draw(m_InfoBird2,m_Handle);
		for(int i=0;i<m_listEffect->size();i++)
		{
			Sprite* tem=m_listEffect->at(i)->m_Effect;
			InfoSprite temif=m_listEffect->at(i)->m_InfoEffect;
			tem->Draw(temif,m_Handle);
		}
		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void StateMainMenu ::Release(){}