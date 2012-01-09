#include "State_Setting.h"
#include "StateMainMenu.h"
#include "SoundGame.h"
StateSetting::StateSetting(iPlay* GamePlay): iState(GamePlay)
{
	m_ID=SETTING;
	Init();
}


StateSetting::~StateSetting(void)
{
}
void StateSetting::Init()
{
	D3DXCreateSprite(m_Device,&m_Handle);
	m_Setting=new Sprite(m_Device,"data\\image\\Setting_State.png",1024,720,1);
	m_Vector=new Sprite(m_Device,"data\\image\\buttonBackSetting.png",88,51,7);
	m_Button=new Sprite(m_Device,"data\\image\\Button_Tick.png",96,55,1);
	m_Tick=new Sprite(m_Device,"data\\image\\Tick.png",42,39,7);
 	m_CountOfEffect=50;
 	m_TimeToUpCount=0;
 	m_listEffect=new vector<Effect_Setting*>();
 	for(int i=0;i<m_CountOfEffect;i++)
 	{
 		Effect_Setting *temp=new Effect_Setting(m_Device);
 		m_listEffect->push_back(temp);
 
 	}
	m_TestButton=SoundGame::Instance()->GetSound();
	m_InfoSetting.setSize(1024,720);
 	m_InfoVector.setSize(88,51);
 	m_InfoVector.setXY(10,500);
 	m_InfoVector.setScaleXY(1.5,1.5);
	m_InfoButton.setXY(450,260);
	m_InfoTick.setXY(480,265);
	m_InfoButton.setSize(96,55);
	m_InfoTick.setColorAlpha(1);
 	m_AniTime=0;
 	test=false;
	m_TestClick=false;
}

void StateSetting ::ProcessMouse(DIMOUSESTATE MouseState,POINT Positon)
{
 	if(MouseState.rgbButtons[0])
 	{
 		if(Positon.x >m_InfoVector.getX() && Positon.x <=m_InfoVector.getX()+m_InfoVector.m_Width
 			&&Positon.y >= m_InfoVector.getY()-30 && Positon.y <=m_InfoVector.getY()+m_InfoVector.m_Height)
 		{
 			m_InfoVector.setScaleXY(1.3f,1.3f);		
 			m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
 		}
 		else
 		{
 			m_InfoVector.setScaleXY(1.5,1.5);
 		}
		if(Positon.x >m_InfoButton.getX() && Positon.x <=m_InfoButton.getX()+m_InfoButton.m_Width
			&&Positon.y >= m_InfoButton.getY()-30 && Positon.y <=m_InfoButton.getY()+m_InfoButton.m_Height)
		{
			m_InfoButton.setScaleXY(0.8f,0.8f);	
			if(m_TestClick==false)		
			{
				if(m_TestButton==true)
					m_TestButton=false;
				else
					m_TestButton=true;
			}
			m_TestClick=true;
		}
		else
		{
			m_InfoButton.setScaleXY(1,1);
			m_TestClick=false;
		}
 	}
	else
	{
		if(Positon.x >m_InfoButton.getX() && Positon.x <=m_InfoButton.getX()+m_InfoButton.m_Width
			&&Positon.y >= m_InfoButton.getY()-30 && Positon.y <=m_InfoButton.getY()+m_InfoButton.m_Height)
		{
			m_InfoButton.setScaleXY(1,1);	
			m_TestClick=false;
		}
		else
		{
			m_InfoButton.setScaleXY(1,1);
			m_TestClick=false;
		}
		if(Positon.x >m_InfoVector.getX() && Positon.x <=m_InfoVector.getX()+m_InfoVector.m_Width
			&&Positon.y >= m_InfoVector.getY()-30 && Positon.y <=m_InfoVector.getY()+m_InfoVector.m_Height)
		{
			m_InfoVector.setScaleXY(1.7f,1.7f);		
			test=true;
		}
		else
		{
			m_InfoVector.setScaleXY(1.5,1.5);
			test=false;
			m_InfoVector.setCurFrame(0);
		}
	}
}
void StateSetting ::Update(float _Time)
{
	if(m_TestButton==true)
	{
		SoundGame::Instance()->SetSound(true);
		SoundGame::Instance()->PlaySoundSetting();
	}
	else
	{
		SoundGame::Instance()->SetSound(false);
		SoundGame::Instance()->StopSoundSetting();
	}		

 	m_TimeToUpCount+=_Time;
 	if(m_TimeToUpCount>=0.1)
 	{
 
 		for (std::vector<Effect_Setting*>::iterator i = m_listEffect->begin();i<m_listEffect->end();i++)
 		{	
 			(*i)->m_timeLife+=0.1;
 			if((*i)->m_timeLife>=(*i)->m_Old)
 			{
 				(*i)->Repress();
 			}
 			(*i)->m_InfoEffect.setColorAlpha((*i)->m_InfoEffect.getColor().a-0.1);
 		}
 		m_TimeToUpCount=0;
 	}
 	m_AniTime+=_Time;
 	if(m_AniTime>=0.15)
 	{
 		m_AniTime-=0.15;
 		if(test==true)
 		{
 			m_InfoVector.NextFrame(0,4);
 			if(m_InfoVector.getCurFrame()>=3)
 			{
 				m_InfoVector.setCurFrame(0);
 			}
 		}
		if(m_TestButton==true)
		{
			m_InfoTick.setColorAlpha(m_InfoTick.getColor().a+0.2);
			if(m_InfoTick.getColor().a>=1)
				m_InfoTick.setColorAlpha(1);
		}
		else
		{
			m_InfoTick.setColorAlpha(m_InfoTick.getColor().a-0.2);
			if(m_InfoTick.getColor().a<=0)
				m_InfoTick.setColorAlpha(0);
		}

 	}

}
void StateSetting ::Draw()
{
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(71,168,208),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);

		m_Setting->Draw(m_InfoSetting,m_Handle);
 		m_Vector->Draw(m_InfoVector,m_Handle);
		m_Button->Draw(m_InfoButton,m_Handle);
		m_Tick->Draw(m_InfoTick,m_Handle);
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
void StateSetting ::Release()
{
	if (m_Setting!= NULL)
	{
		m_Setting->Release();
		delete m_Setting;
		m_Setting = NULL;
	}
	if (m_Vector!= NULL)
	{
		m_Vector->Release();
		delete m_Vector;
		m_Vector = NULL;
	}
	if (m_Button!= NULL)
	{
		m_Button->Release();
		delete m_Button;
		m_Button = NULL;
	}
	if (m_Tick!= NULL)
	{
		m_Tick->Release();
		delete m_Tick;
		m_Tick = NULL;
	}
	if (m_Handle!=NULL)
	{
		m_Handle->Release();
		m_Handle = NULL;
	}
	for(int i=0;i<m_listEffect->size();i++)
	{
		Sprite* tem=m_listEffect->at(i)->m_Effect;
		if(tem!=NULL)
		{
			tem->Release();
		}
	}
}