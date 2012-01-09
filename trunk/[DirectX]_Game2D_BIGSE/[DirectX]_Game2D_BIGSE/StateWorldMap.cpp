#include "StateWorldMap.h"
#include "RSMainGame.h"
#include "Global.h"
#include "State_Play.h"
#include "State_Loading.h"
#include "RECT.h"
#include "StateMainMenu.h"
#include "SoundGame.h"

StateWorldMap::StateWorldMap(iPlay *GamePlay,int _IDHero) : iState(GamePlay)
{
	m_ID = WorldMap ;
	m_IDHero = _IDHero;
}


StateWorldMap::~StateWorldMap(void)
{
}
void StateWorldMap ::Init()
{
	
	m_TimeAni = 0 ;
	m_STT = ACTIVE ;
	D3DXCreateSprite(m_Device,&m_Handle);

	m_WorldMap = new Sprite(m_Device,"data\\image\\WorldMap.png",1024,720,1) ;
	m_Character = new Sprite(m_Device,"data\\image\\Bear-Move.png",78,87,8);
	m_CharacterAttack = new Sprite(m_Device,"data\\image\\BearAttack.png",114,104,10);

	m_InfoSprite.setSize(1024,720);
	m_InfoCharacter.setSize(78,87) ;
	m_InfoCharacter.setXY(100,100) ;
	m_InfoAttack.setSize(114,104) ;

	
	r.Left = m_InfoCharacter.getX() ;
	r.Top =  m_InfoCharacter.getY() ;
	r.Right = r.Left + 78;
	r.Bottom = r.Top + 87;

	Perion.Left = 492 ;
	Perion.Top = 151 ;
	Perion.Right = 586 ;
	Perion.Bottom = 182;

	Kerningstadt.Left = 233 ;
	Kerningstadt.Right = 328 ;
	Kerningstadt.Top = 311;
	Kerningstadt.Bottom = 340 ;

	Kerningplatz.Left = 42 ;
	Kerningplatz.Right = 160 ;
	Kerningplatz.Top = 340 ;
	Kerningplatz.Bottom = 369 ;

	LithHafen.Left = 120 ;
	LithHafen.Right = 217 ;
	LithHafen.Top = 465 ;
	LithHafen.Bottom = 497 ;

	Henesys.Left = 393 ;
	Henesys.Right = 487 ;
	Henesys.Top = 504;
	Henesys.Bottom =531 ;

	SechsWegeKreuzung.Left = 398 ;
	SechsWegeKreuzung.Right = 512 ;
	SechsWegeKreuzung.Top = 365 ;
	SechsWegeKreuzung.Bottom = 395 ;

	Ellinia.Left = 608 ;
	Ellinia.Right = 703 ;
	Ellinia.Top = 419 ;
	Ellinia.Bottom = 450 ;

	Nautilus.Left = 612;
	Nautilus.Right = 706 ;
	Nautilus.Top = 550 ;
	Nautilus.Bottom = 586 ;

	FloringStrand.Left = 830 ;
	FloringStrand.Right = 953 ;
	FloringStrand.Top= 568 ;
	FloringStrand.Bottom = 598 ;
}

void StateWorldMap ::ProcessMouse(DIMOUSESTATE MouseState,POINT Positon)
{
	if(MouseState.rgbButtons[0])
	{
		if(Positon.x > 495 && Positon.x < 587) //Level Perion 
		{
			if(Positon.y > 152 && Positon.y < 182)
			{
				m_iPlay->SetNextState(new State_Loading(this->m_iPlay,"data\\map\\6.png",m_IDHero));
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
void StateWorldMap ::IsKeyDown(int KeyCode)
{
	switch(KeyCode)
	{
	case DIK_LEFT:
		m_InfoCharacter.setX(m_InfoCharacter.getX() - 0.1) ;

		r.Left = m_InfoCharacter.getX() ;
		r.Top =  m_InfoCharacter.getY() ;
		r.Right = r.Left + 78;
		r.Bottom = r.Top + 87;

		m_InfoCharacter.setScaleX(1);
		break ;

	case DIK_RIGHT :
		m_InfoCharacter.setX(m_InfoCharacter.getX() + 0.1) ;
		m_InfoCharacter.setScaleX(-1);

		r.Left = m_InfoCharacter.getX() ;
		r.Top =  m_InfoCharacter.getY() ;
		r.Right = r.Left + 78;
		r.Bottom = r.Top + 87;
		break ;
	case DIK_DOWN :
		m_InfoCharacter.setY(m_InfoCharacter.getY() + 0.1) ;

		r.Left = m_InfoCharacter.getX() ;
		r.Top =  m_InfoCharacter.getY() ;
		r.Right = r.Left + 78;
		r.Bottom = r.Top + 87 ;

		break ;
	case DIK_UP:
		m_InfoCharacter.setY(m_InfoCharacter.getY() - 0.1) ;

		r.Left = m_InfoCharacter.getX() ;
		r.Top =  m_InfoCharacter.getY() ;
		r.Right = r.Left + 78 ;
		r.Bottom = r.Top + 87;
		break ;
	}
	
}
void StateWorldMap :: OnKeyDown(int KeyCode)
{
	switch(KeyCode)
	{
	case DIK_NUMPAD1 :
		m_STT = READY ;
		break ;
	}
}

void StateWorldMap ::Update(float _Time)
{
	if(r.iCollision(Perion) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new State_Loading(this->m_iPlay,"data\\map\\6.png",m_IDHero));
	}
	if(r.iCollision(Kerningstadt) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}
	if(r.iCollision(Kerningplatz) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}
	if(r.iCollision(LithHafen) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}
	if(r.iCollision(Henesys) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}
	if(r.iCollision(SechsWegeKreuzung) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}
	if(r.iCollision(Ellinia) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}
	if(r.iCollision(Nautilus) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}
	if(r.iCollision(FloringStrand) == true  && m_STT == READY  && m_InfoAttack.getCurFrame()>5)
	{
		m_iPlay->SetNextState(new StateMainMenu(this->m_iPlay));
	}


	m_TimeAni += _Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			m_InfoCharacter.NextFrame(0,7);
		}
		break;
	case READY :
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			m_InfoAttack.NextFrame(0,9);
			if(m_InfoAttack.getCurFrame() == 8  )
			{
				m_STT = ACTIVE ;
			}
		}
		break;
	}
}
void StateWorldMap ::Draw()
{
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);
		m_WorldMap->Draw(m_InfoSprite,m_Handle);
		if(m_STT ==ACTIVE)
		{
		    m_Character->Draw(m_InfoCharacter,m_Handle);
		}
		if(m_STT ==READY )
		{
			if(m_InfoCharacter.getScaleX() ==1)
			{
				m_InfoAttack.setScaleX(1);
			}
			if(m_InfoCharacter.getScaleX() ==-1)
			{
				m_InfoAttack.setScaleX(-1);
			}
			m_InfoAttack.setXY(m_InfoCharacter.getX() -5,m_InfoCharacter.getY() - 10) ;
			m_CharacterAttack->Draw(m_InfoAttack,m_Handle);
		}
		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void StateWorldMap ::Release()
{
	if (m_Character!= NULL)
	{
		m_Character->Release();
		delete m_Character;
		m_Character = NULL;
	}
	if (m_CharacterAttack!= NULL)
	{
		m_CharacterAttack->Release();
		delete m_CharacterAttack;
		m_CharacterAttack = NULL;
	}
	if (m_WorldMap!= NULL)
	{
		m_WorldMap->Release();
		delete m_WorldMap;
		m_WorldMap = NULL;
	}
	if (m_Handle!=NULL)
	{
		m_Handle->Release();
		m_Handle = NULL;
	}
}

	 

