#include "State_Game.h"
#include <dinput.h>
#include "Global.h"
#include "State_Play.h"


MainGame::MainGame(iPlay* GamePlay)
	:iState(GamePlay)
{
	m_ID = ABOUT;
	m_Ro = 0;
	m_ScaleX=1;
	m_ScaleY =1;
}


MainGame::~MainGame(void)
{
}

void MainGame::IsKeyDown(int KeyCode)
{
	switch(KeyCode)
	{
	case DIK_LEFT:
		m_infoSprite.setX(m_infoSprite.getX()-2);
		break;
	case DIK_RIGHT:
		m_infoSprite.setX(m_infoSprite.getX()+2);
		break;
	case DIK_UP:
		m_infoSprite.setY(m_infoSprite.getY()-2);
		break;
	case DIK_DOWN:
		m_infoSprite.setY(m_infoSprite.getY()+2);
		break;
	case DIK_NUMPAD8:
		m_infoSprite.setScaleY(m_infoSprite.getScaleY()+0.1f);
		break;
	case DIK_NUMPAD2:
		m_infoSprite.setScaleY(m_infoSprite.getScaleY()-0.1f);
		break;
	case DIK_NUMPAD4:
		m_infoSprite.setScaleX(m_infoSprite.getScaleX()-0.1f);
		break;
	case DIK_NUMPAD6:
		m_infoSprite.setScaleX(m_infoSprite.getScaleX()+0.1f);
		break;
	case DIK_NUMPAD1:
		m_infoSprite.setRotation(m_infoSprite.getRotation()+1);
		break;
	case DIK_NUMPAD3:
		m_infoSprite.setRotation(m_infoSprite.getRotation()-1);
		break;
	case DIK_Q:
		m_Ro++;
		break;
	case DIK_E:
		m_Ro--;
		break;
	case DIK_W:
		m_ScaleY+=0.1f;
		break;
	case DIK_S:
		m_ScaleY-=0.1f;
		break;
	case DIK_A:
		m_ScaleX-=0.1f;
		break;
	case DIK_D:
		m_ScaleX+=0.1f;
		break;

	case DIK_SPACE:
		this->GetGamePlay()->SetNextState(
			new State_Play(this->GetGamePlay()));
		break;
	}
}
void MainGame::OnKeyDown(int KeyCode)
{
	switch(KeyCode)
	{

	}
}
void MainGame::OnKeyUp(int KeyCode)
{
	switch(KeyCode)
	{

	}
}
void MainGame::Init()
{
	m_sMario = new Sprite(m_Device,"data\\image\\mario.png",50,100,5);
	D3DXCreateSprite(m_Device,&m_Handle);
	m_infoSprite.setSize(50,100);
	m_infoSprite.setXY(100,100);
	/*m_infoSprite.setRotation(90);*/
	
}
void MainGame::Update(float _Time)
{

}
void MainGame::Draw()
{
	D3DXMATRIX mtView;
	D3DXMatrixIdentity(&mtView);
	D3DXMatrixTransformation2D(&mtView,NULL,0,NULL,NULL,NULL,
		&D3DXVECTOR2(50,100));
	m_Handle->SetWorldViewLH(NULL,&mtView);
	m_Device->SetTransform(D3DTS_VIEW,&mtView);
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,255,255),1.0f,0);
	if(m_Device->BeginScene())
	{
		

		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);

		

		m_sMario->Draw(100,100,2,m_Handle);


		D3DXMATRIX MaTrix,Ma;

		D3DXVECTOR2 Center (g_SCREEN_WIDTH/2,g_SCREEN_HEIGHT/2);
		D3DXVECTOR2 MTScale(m_ScaleX,m_ScaleY);
		D3DXVECTOR2 MTTran (0,0);

		float Rota = (float)(m_Ro*2*D3DX_PI)/(float)(360);

		D3DXMatrixTransformation2D(&MaTrix,&Center,0,&MTScale,&Center,Rota,&MTTran);


		//m_sMario->Draw(m_infoSprite,m_Handle);

		m_sMario->Draw(MaTrix,m_infoSprite,m_Handle);


		m_Handle->End();
		m_Device->EndScene();
	}

	m_Device->Present(NULL,NULL,NULL,NULL);
}
void MainGame::Release()
{

}