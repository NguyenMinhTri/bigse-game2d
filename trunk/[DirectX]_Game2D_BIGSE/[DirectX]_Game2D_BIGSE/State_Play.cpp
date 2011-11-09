#include "State_Play.h"
#include "Global.h"
#include "RSMainGame.h"


State_Play::State_Play(iPlay* GamePlay)
	:iState(GamePlay)
{
	m_ID = PLAY;
}


State_Play::~State_Play(void)
{
}

void State_Play::Init()
{

	RSMainGame::get()->IntRS(m_Device);

	D3DXCreateSprite(m_Device,&m_Handle);
	m_char = new Character();
	m_char->Init();
	m_char->setXY(200,0);
	m_char->setSize(50,85);
	int _Terrain [] = {
//      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //0
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, //1
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //2
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, //3
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, //4
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, //5
		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, //6
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, //7
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, //8
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //10		
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, //11
	};

	m_Terrain=new int*[16];
	for(int i=0;i<16;i++)
	{
		m_Terrain[i]=new int[14];
	}


	for (int i =0 ; i< 16; i++)	{
		for (int j = 0 ; j<12; j++)	{			 
			m_Terrain[i][j] = _Terrain[j*16 + i];
		}
	}

}
void State_Play::IsKeyDown(int KeyCode){
	switch(KeyCode)
	{
	case DIK_LEFT:
		m_char->setMove(-1);
		break;
	case DIK_RIGHT:
		m_char->setMove(1);
		break;
	case DIK_SPACE:
		m_char->setJump();
		break;
	
	case DIK_DOWN:
		break;
	}
}


void State_Play::OnKeyDown(int KeyCode)
{
	switch(KeyCode)
	{
	case DIK_V:
		m_char->ActiveSkill();
		break;
	}
}
void State_Play::OnKeyUp(int KeyCode)
{
	switch(KeyCode)
	{

	}
}

void State_Play::Update(float _Time)
{
	m_char->Animation(_Time);
	m_char->Move(_Time,m_Terrain);
	
	m_char->Update(_Time);
	m_char->UpdateStatus(_Time);
}
void State_Play::Draw()
{	
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0f,0);
	/*D3DRECT r;
	r.x1 = m_char->getX();
	r.x2 = r.x1 + 50;
	r.y1 = m_char->getY();
	r.y2 = r.y1 + 85;
	m_Device->Clear(1,&r,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,0,255),1.0f,0);*/
	
	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);
		
		for (int i =0 ; i< 16; i++)	{
			for (int j = 0 ; j<14; j++)	{
				if(m_Terrain[i][j] == 1){
					RSMainGame::get()->getTerrain()->Draw(i*g_CELL,j*g_CELL-10,0,m_Handle);
				}
				
			}
		}

		m_char->Draw(D3DXMATRIX(),m_Handle);

		

		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void State_Play::Release()
{

}