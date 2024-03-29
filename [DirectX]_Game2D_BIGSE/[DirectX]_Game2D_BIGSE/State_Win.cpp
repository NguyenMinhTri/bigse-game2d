#include "State_Win.h"
#include "StateMainMenu.h"

StateWin::StateWin(iPlay* GamePlay): iState(GamePlay)
{
	m_ID=ABOUT;
	Init();
}


StateWin::~StateWin(void)
{
}
void StateWin::Init()
{
	D3DXCreateSprite(m_Device,&m_Handle);
	m_Win=new Sprite(m_Device,"data\\image\\State_Win.png",1024,720,1);
	m_Vector=new Sprite(m_Device,"data\\image\\buttonBack.png",88,51,7);
	m_CountOfEffect=30;
	m_TimeToUpCount=0;
	m_listEffect=new vector<Effect_Setting*>();
	for(int i=0;i<m_CountOfEffect;i++)
	{
		Effect_Setting *temp=new Effect_Setting(m_Device);
		m_listEffect->push_back(temp);

	}
	m_InfoWin.setSize(1024,720);
	m_InfoVector.setSize(88,51);
	m_InfoVector.setXY(80,480);
	m_InfoVector.setScaleXY(1.5,1.5);

	m_AniTime=0;
	test=false;
}
void StateWin ::ProcessMouse(DIMOUSESTATE MouseState,POINT Positon)
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
	}
	else
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
void StateWin ::Update(float _Time)
{
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
	}

}
void StateWin ::Draw()
{
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(71,168,208),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);

		m_Win->Draw(m_InfoWin,m_Handle);
		m_Vector->Draw(m_InfoVector,m_Handle);
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
void StateWin ::Release()
{
	if (m_Handle!=NULL)
	{
		m_Handle->Release();
		m_Handle = NULL;
	}
	if (m_Win!= NULL)
	{
		m_Win->Release();
		delete m_Win;
		m_Win = NULL;
	}
	if (m_Vector!= NULL)
	{
		m_Vector->Release();
		delete m_Vector;
		m_Vector = NULL;
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