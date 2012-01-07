#include "StatePlayer.h"
#include "RSMainGame.h"
#include "Global.h"
#include "StateWorldMap.h"
#include "State_Play.h"


StatePlayer::StatePlayer(iPlay *GamePlay) : iState(GamePlay)
{
	m_ID = ChoosePlayer ;
}


StatePlayer::~StatePlayer(void)
{
}
void StatePlayer ::Init()
{
	g_STT =READY;
	t_STT = READY;
	z_STT = READY ;
	m_TimeAni = 0;
	D3DXCreateSprite(m_Device,&m_Handle);
	m_SwordMan = new Sprite(m_Device,"data\\image\\Choose_Sword.png",300,326,1) ;
	m_InfoSword.setSize(300,326);
	m_InfoSword.setXY(0,200);

	m_BackGround = new Sprite(m_Device,"data\\image\\BackGroundChoose.png",1024,720,1) ;
	m_InfoSword.setSize(1024,720);
	
	m_Magician = new Sprite (m_Device,"data\\image\\Choose_Magician.png",300,322,1) ;
	m_InfoMagician.setSize(300,322);
	m_InfoMagician.setXY(350,200);

	m_Punch =  new Sprite (m_Device,"data\\image\\Choose_Punch.png",300,343,1) ;
	m_InfoPunch.setSize(300,343);
	m_InfoPunch.setXY(700,200);

	m_Flag = new Sprite (m_Device,"data\\image\\Flag.png",97,134,4) ;
	m_InfoFlag.setSize(97,134) ;
}


void StatePlayer:: ProcessMouse(DIMOUSESTATE MouseState,POINT Positon) 
{
	if(MouseState.rgbButtons[0])
	{
		if(Positon.x >=1 && Positon.x <=300 &&Positon.y >= 200 && Positon.y <=526)
		{
			m_iPlay->SetNextState(new StateWorldMap(this->m_iPlay));//chua dat ID
		}
		if(Positon.x >=350 && Positon.x<=650 && Positon.y >=200 && Positon.y <=522)
		{
			m_iPlay->SetNextState(new StateWorldMap(this->m_iPlay));//chua dat ID
		}
		if(Positon.x >=700 &&Positon.x <=1000 && Positon.y>=200 && Positon.y<=543)
		{
			m_iPlay->SetNextState(new StateWorldMap(this->m_iPlay)); //chua dat ID 
		}
	}

		if(Positon.x >=1 && Positon.x <=300 &&Positon.y >= 200 && Positon.y <=526)
		{
				g_STT = ACTIVE ;
				m_InfoFlag.setXY(100,50 );
		}
		else{g_STT =READY ; }	

		if(Positon.x >=350 && Positon.x<=650 && Positon.y >=200 && Positon.y <=522)
		{
			t_STT = TIME ;
			m_InfoFlag.setXY(480,50);
		}
		else {t_STT =READY;}
		if(Positon.x >=700 &&Positon.x <=1000 && Positon.y>=200 && Positon.y<=543)
		{
			z_STT = TIME ;
			m_InfoFlag.setXY(810,50);
		}
		else{z_STT = READY;}

		
}
void StatePlayer::Update(float _Time)
{
	m_TimeAni += _Time ;
	switch (g_STT )
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			m_InfoFlag.NextFrame(0,3);
		}
	}
	switch (t_STT )
	{
	case TIME:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			m_InfoFlag.NextFrame(0,3);
		}
	}
	switch (z_STT )
	{
	case TIME:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			m_InfoFlag.NextFrame(0,3);
		}
	}
}
void StatePlayer ::Draw()
{
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);
		m_BackGround->Draw(m_InfoBG,m_Handle);

		m_SwordMan->Draw(m_InfoSword,m_Handle) ;

		if(g_STT == ACTIVE || t_STT==TIME || z_STT ==TIME)
		{
		   m_Flag->Draw(m_InfoFlag,m_Handle);
		}
		m_Magician->Draw(m_InfoMagician,m_Handle);
		m_Punch->Draw(m_InfoPunch,m_Handle);
		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void StatePlayer::Release(){}