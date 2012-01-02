#include "State_Play.h"
#include "Global.h"
#include "RSMainGame.h"
#include "ManagerObject.h"


State_Play::State_Play(iPlay* GamePlay)
	:iState(GamePlay)
{
	m_ID = PLAY;
	m_STT = READY ;
}


State_Play::~State_Play(void)
{
}

void State_Play::Init()
{

	RSMainGame::get()->IntRS(m_Device);	

	m_ListItem = new std::vector<MyObject*>();
	m_ObjectsCamera = new std::vector<MyObject*>();
	m_ListMonster = new std ::vector<MyObject*>();
	m_ListEffect = new std::vector<EffectSystem*>();
	m_ListBoss = new std ::vector<MyObject*>();

	ManagerObject::Instance()->setListObject(m_ListItem);
	ManagerObject::Instance()->setObjects(m_ObjectsCamera);
	ManagerObject::Instance()->setListEffect(m_ListEffect);
	ManagerObject::Instance()->setListMonster(m_ListMonster);
	ManagerObject::Instance()->setListBoss(m_ListBoss);

	D3DXCreateSprite(m_Device,&m_Handle);

	m_Camera = new Camera(0,0,g_SCREEN_WIDTH,g_SCREEN_HEIGHT);
	#pragma region Init Item


	#pragma region Init Character
    m_char = new Character();
	m_char->Init();
	m_char->setXY(200,0);
	m_char->setSize(50,85);
	

	m_Monster = new Character();
	m_Monster->Init();
	m_Monster->setXY(1000,460);
	m_Monster->setSize(50,85);

	m_Monster1 = new Monster();
	m_Monster1->setXY(60,460);

	m_Monster2 = new Monster();
	m_Monster2->setXY(100,460);



	m_Archer = new Archer();
	m_Archer->Init();
	m_Archer->setXY( 200,0);
	m_Archer->setSize(50,85);

	m_Magician = new Magician();
	m_Magician->Init();
	m_Magician->setXY( 200,0);
	m_Magician->setSize(50,85);

	m_Angle = new Angle();

	m_GodLike = new GodLike_Beast() ;
	m_GodLike->setXY(50,100);

	m_SnakeMan=new SnakeMans();
	m_SnakeMan->setXY(450,0);

	m_Hero=new Hero();
	m_Hero->setXY(0,0);

	m_ObjectsCamera->push_back(m_Hero);


#pragma endregion Init Character

	#pragma region Init Map Terrain

	m_LoadMap = new LoadMap();
	m_LoadMap->LoadMapFormFile("data\\map\\6.png",m_Device);

	int m = m_LoadMap->m_Width > m_LoadMap->m_Height ? m_LoadMap->m_Width : m_LoadMap->m_Height;

	m_QuadTree = new QuadTree(CRECT(0,m*50,0,50*m));
	ManagerObject::Instance()->setQuadTree(m_QuadTree);

	m_LoadMap->TranslateMap();

	m_Map = new Terrain(m_LoadMap->m_Terrain,m_LoadMap->m_TerrainExtends,m_LoadMap->m_Width,m_LoadMap->m_Height);
#pragma endregion Init Map Terrain

	D3DXMatrixIdentity(&m_mtWorld);

	
}
void State_Play::IsKeyDown(int KeyCode)
{
	switch(KeyCode)
	{
		// 	case DIK_LEFT:
		// 	m_Monster->setMove(-1);
		// 		break;
		// 	case DIK_RIGHT:
		// 	m_Monster->setMove(1);
		// 	  break;
		// 	case DIK_UP:
		// 	m_Monster->setJump();
		
	case DIK_A:
		m_Hero->setMove(-1);
		break;
	case DIK_D:
		m_Hero->setMove(1);
		break;
	case DIK_W:
		m_Hero->setJump();
		break;

	case DIK_DOWN:
		break;
	}
}

void State_Play::OnKeyDown(int KeyCode)
{
	switch(KeyCode)
	{

	case DIK_NUMPAD7:
		m_GodLike->ActiveSkill(3);
		break ;

	case DIK_F:
		m_Hero->ActiveSkill(0);
		break ;
	case DIK_E:
		m_Hero->ActiveSkill(1);
		break ;
	case DIK_R:
		m_Hero->ActiveSkill(2);
		break ;
	case DIK_NUMPAD1:
		m_Archer->ActiveSkill(0);
		break;
	case DIK_NUMPAD4:
		m_Angle->ActiveSkill(0);
		break;
	case DIK_NUMPAD5:
		m_Angle->ActiveSkill(1);
		break;

	case DIK_NUMPAD9:
		m_STT = FREEZETIME ;

		// 	case DIK_NUMPAD4:
		// 		 m_Magician->ActiveSkill(0);
		// 		 break;
	case DIK_H:
		m_Monster->ActiveSkill(4);
		break;
	case DIK_J:
		m_Monster->ActiveSkill(1);
		break;
	case DIK_L:
		m_Monster->ActiveSkill(3);
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
	m_Camera->Update(m_Hero,m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
	//m_Camera->UpdateEffect(_Time);
	m_mtWorld = m_Camera->getMatrixTransform();

	/************************************************************************/
	/*  Update QuadTree                                                     */
	/************************************************************************/

	for (std::vector<MyObject*>::iterator i = m_ListMonster->begin();i!= m_ListMonster->end();)
	{
		
		if(!m_Camera->getRect().iCollision((*i)->getRect()))
		{
			m_QuadTree->Insert((*i));
			i= m_ListMonster->erase(i);
		}
		else i++;		
	}

	std::vector<MyObject*> *Query = m_QuadTree->Query(m_Camera->getRect());
	m_ListMonster->insert(m_ListMonster->begin(),Query->begin(),Query->end());
	delete  Query;

	/************************************************************************/
	/*  Update all item                                                     */
	/************************************************************************/
	for (std::vector<MyObject*>::iterator i = m_ListItem->begin();i!= m_ListItem->end();)
	{
		(*i)->Update(_Time,m_Map->getTerrain(),m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
		if ((*i)->getLife()==false)
		{
			(*i)->Release();
			i =m_ListItem->erase(i);
			continue;
		}
		i++;
	}
	/************************************************************************/
	/*  Update Object in camera                                             */
	/************************************************************************/	
	for (std::vector<MyObject*>::iterator i = m_ObjectsCamera->begin();i!= m_ObjectsCamera->end();)
	{
		(*i)->Update(_Time,m_Map->getTerrain(),m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
		if( (*i)->getLife() == false)
		{
			(*i)->Release();
			i = m_ObjectsCamera->erase(i);
			continue;
		}
		i++;		
	}
	/************************************************************************/
	/*  Update Monster in camera                                             */
	/************************************************************************/	
	for (std::vector<MyObject*>::iterator i = m_ListMonster->begin();i!= m_ListMonster->end();)
	{
		(*i)->Update(_Time,m_Map->getTerrain(),m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
		if( (*i)->getLife() == false)
		{
			(*i)->Release();
			i = m_ListMonster->erase(i);
			continue;
		}
		i++;		
	}
	/************************************************************************/
	/*  Update Effect in camera                                             */
	/************************************************************************/	
	for (std::vector<EffectSystem*>::iterator i = m_ListEffect->begin();i!= m_ListEffect->end();)
	{
		(*i)->Update(_Time);
		if( (*i)->m_iLife == false)
		{
			(*i)->Release();
			i = m_ListEffect->erase(i);
			continue;
		}
		i++;		
	}
	/************************************************************************/
	/*  Collision Object vs Object                                          */
	/************************************************************************/	
	for (std::vector<MyObject*>::iterator i = m_ObjectsCamera->begin();i!= m_ObjectsCamera->end();i++)
	{		
		for (std::vector<MyObject*>::iterator j = (i+1);j!= m_ObjectsCamera->end();j++)
		{
			(*i)->ProcessCollision(*j);
			(*j)->ProcessCollision(*i);
		}		
	}
	/************************************************************************/
	/*  Collision Object vs Monster                                        */
	/************************************************************************/	
	for (std::vector<MyObject*>::iterator i = m_ObjectsCamera->begin();i!= m_ObjectsCamera->end();i++)
	{		
		for (std::vector<MyObject*>::iterator j = m_ListMonster->begin();j!= m_ListMonster->end();j++)
		{
			(*i)->ProcessCollision(*j);
			(*j)->ProcessCollision(*i);
		}		
	}
	/************************************************************************/
	/*  Collision Object vs item                                            */
	/************************************************************************/
	for (std::vector<MyObject*>::iterator i = m_ObjectsCamera->begin();i!= m_ObjectsCamera->end();i++)
	{		
		for (std::vector<MyObject*>::iterator j = m_ListItem->begin();j!= m_ListItem->end();j++)
		{
			(*i)->ProcessCollision(*j);
			(*j)->ProcessCollision(*i);
		}		
	}

	for (std::vector<MyObject*>::iterator i = m_ListBoss->begin();i!= m_ListBoss->end();)
	{
		(*i)->Update(_Time,m_Map->getTerrain(),m_Map->getWidth()*g_CELL,m_Map->getHeight()*g_CELL);
		if( (*i)->getLife() == false)
		{
			(*i)->Release();
			i = m_ListBoss->erase(i);
			continue;
		}
		i++;  
	}

	/************************************************************************/
	/*  Collision Object vs Boss                                       */
	/************************************************************************/ 
	for (std::vector<MyObject*>::iterator i = m_ObjectsCamera->begin();i!= m_ObjectsCamera->end();i++)
	{  
		for (std::vector<MyObject*>::iterator j = m_ListBoss->begin();j!= m_ListBoss->end();j++)
		{
			(*i)->ProcessCollision(*j);
			(*j)->ProcessCollision(*i);
		}  
	}
}

void State_Play::Draw()
{	
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);
		
 		m_Map->Draw(m_Camera,m_mtWorld,m_Handle);

		for (std::vector<MyObject*>::iterator i = m_ObjectsCamera->begin();i!= m_ObjectsCamera->end();i++)
		{
			(*i)->Draw(m_mtWorld,m_Handle);			

		}
		for (std::vector<MyObject*>::iterator i = m_ListMonster->begin();i!= m_ListMonster->end();i++)
		{
			(*i)->Draw(m_mtWorld,m_Handle);			

		}

		for (std::vector<MyObject*>::iterator i = m_ListItem->begin();i!= m_ListItem->end();i++)
		{
			(*i)->Draw(m_mtWorld,m_Handle);			
		}

		for (std::vector<EffectSystem*>::iterator i = m_ListEffect->begin();i!= m_ListEffect->end();i++)
		{
			(*i)->Draw(m_mtWorld,m_Handle);			
		}

		for (std::vector<MyObject*>::iterator i = m_ListBoss->begin();i!= m_ListBoss->end();i++)
		{
			(*i)->Draw(m_mtWorld,m_Handle);   
		}
		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void State_Play::Release()
{

}