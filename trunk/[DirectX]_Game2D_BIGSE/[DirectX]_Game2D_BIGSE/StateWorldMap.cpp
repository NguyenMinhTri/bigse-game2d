#include "StateWorldMap.h"
#include "RSMainGame.h"
#include "Global.h"
#include "State_Play.h"
#include "State_Loading.h"

StateWorldMap::StateWorldMap(iPlay *GamePlay) : iState(GamePlay)
{
	m_ID = WorldMap ;
}


StateWorldMap::~StateWorldMap(void)
{
}
void StateWorldMap ::Init()
{

	D3DXCreateSprite(m_Device,&m_Handle);

	m_WorldMap = new Sprite(m_Device,"data\\image\\WorldMap.png",1024,720,1) ;

	m_InfoSprite.setSize(1024,720);
}

void StateWorldMap ::ProcessMouse(DIMOUSESTATE MouseState,POINT Positon)
{
	if(MouseState.rgbButtons[0])
	{
		if(Positon.x > 495 && Positon.x < 587) //Level Perion 
		{
			if(Positon.y > 152 && Positon.y < 182)
			{
				m_iPlay->SetNextState(new State_Loading(this->m_iPlay,"data\\map\\6.png"));
			}
		}
		if(Positon.x > 606 && Positon.x < 701) //Ellina
		{
			if(Positon.y > 418 && Positon.y < 452)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
		if(Positon.x > 401 && Positon.x < 515) //Sechs Weg kreuzung
		{
			if(Positon.y > 365 && Positon.y < 395)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
		if(Positon.x > 235 && Positon.x < 331) //Kerningstadt
		{
			if(Positon.y > 310 && Positon.y < 340)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
		if(Positon.x > 48 && Positon.x < 158) //kerningplatz
		{
			if(Positon.y > 339 && Positon.y < 370)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
		if(Positon.x > 121 && Positon.x < 216)  //Lith-Hafen
		{
			if(Positon.y > 467 && Positon.y < 495)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
		if(Positon.x > 392 && Positon.x < 485) //Henesys
		{
			if(Positon.y > 501 && Positon.y < 532)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
		if(Positon.x > 612 && Positon.x < 706) //Nautilus
		{
			if(Positon.y > 552 && Positon.y < 584)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
		if(Positon.x > 830 && Positon.x < 956) //Floringstrand 
		{
			if(Positon.y > 568 && Positon.y < 600)
			{
				/*m_iPlay->SetNextState(new State_Play(this->m_iPlay));*/
			}
		}
	}

}
void StateWorldMap ::Update(float _Time){}
void StateWorldMap ::Draw()
{
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);
		m_WorldMap->Draw(m_InfoSprite,m_Handle);
		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void StateWorldMap ::Release(){}

	 

