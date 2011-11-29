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

	m_Camera = new Camera(0,0,g_SCREEN_WIDTH,g_SCREEN_HEIGHT);

	#pragma region Init Character
    m_char = new Character();
	m_char->Init();
	m_char->setXY(200,0);
	m_char->setSize(50,85);
	
	m_Monster = new Character();
	m_Monster->Init();
	m_Monster->setXY(200,0);
	m_Monster->setSize(50,85);

	m_Monster1 = new Monster();
	m_Monster1->Init();
	m_Monster1->setXY(60,460);
	m_Monster1->setSize(50,85);


#pragma endregion Init Character

	#pragma region Init Map Terrain
int _Terrain [] = {
//      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //0
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //1
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //2
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //3
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //4
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //5
		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //6
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //7
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //8
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //9
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //10		
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //11
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //12
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //13
	};
	int **m_Terrain; 
	m_Terrain=new int*[32];
	for(int i=0;i<32;i++)
	{
		m_Terrain[i]=new int[14];
	}


	for (int i =0 ; i< 32; i++)	{
		for (int j = 0 ; j<14; j++)	{			 
			m_Terrain[i][j] = _Terrain[j*32 + i];
		}
	}
	m_Map = new Terrain(m_Terrain,32,14);
#pragma endregion Init Map Terrain

	D3DXMatrixIdentity(&m_mtWorld);
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
	case DIK_UP:
		m_char->setJump();
		break;
	

	case DIK_A:
		m_Monster->setMove(-1);
		break;
	
	case DIK_D:
		m_Monster->setMove(1);
		break;
	case DIK_W:
		m_Monster->setJump();
		break;

	case DIK_DOWN:
		break;
	}
}

void State_Play::OnKeyDown(int KeyCode)
{
	switch(KeyCode)
	{
	case DIK_NUMPAD1:
		m_char->ActiveSkill(0);
		break;
	case DIK_NUMPAD2:
		m_char->ActiveSkill(1);
		break;
	case DIK_NUMPAD3:
		m_char->ActiveSkill(2);
		break;
	case DIK_J:
		m_Monster->ActiveSkill(1);
		break;
	case DIK_K:
		m_Monster->ActiveSkill(2);
		break;
	case DIK_SPACE:
		m_Monster->ActiveSkill(0);
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
	m_Camera->Update(m_char,m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
	m_Camera->UpdateEffect(_Time);
	m_mtWorld = m_Camera->getMatrixTransform();

	
	
	m_char->Update(_Time,m_Map->getTerrain(),m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
	
	
	m_Monster->Update(_Time,m_Map->getTerrain(),m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
	m_Monster1->Update(_Time,m_Map->getTerrain(),m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);

	

	m_char->ProcessCollision(m_Monster);
	m_Monster->ProcessCollision(m_char);
	m_Monster1->ProcessCollision(m_char);
	m_Monster1->ProcessCollision(m_Monster);

}
void State_Play::Draw()
{	
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0f,0);

	
	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);
		
		m_Map->Draw(m_Camera,m_mtWorld,m_Handle);

		m_char->Draw(m_mtWorld,m_Handle);
		m_Monster->Draw(m_mtWorld,m_Handle);
		m_Monster1->Draw(m_mtWorld,m_Handle);
	


		

		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void State_Play::Release()
{

}