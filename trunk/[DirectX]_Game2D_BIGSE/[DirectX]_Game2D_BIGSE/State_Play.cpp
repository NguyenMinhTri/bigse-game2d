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
	m_SpecialObject = new std ::vector<MyObject*>();

	ManagerObject::Instance()->setListObject(m_ListItem);
	ManagerObject::Instance()->setObjects(m_ObjectsCamera);
	ManagerObject::Instance()->setListEffect(m_ListEffect);
	ManagerObject::Instance()->setListMonster(m_ListMonster);
	ManagerObject::Instance()->setListBoss(m_ListBoss);
	ManagerObject::Instance()->setSpecialObjects(m_SpecialObject);

	D3DXCreateSprite(m_Device,&m_Handle);

	m_Camera = new Camera(0,0,g_SCREEN_WIDTH,g_SCREEN_HEIGHT);
	#pragma region Init Item


	#pragma region Init Character   
	

	m_Hero=new Hero();
	m_Hero->setXY(0,0);

// 	m_SnakeMans=new SnakeMans();
// 	m_SnakeMans->setXY(1200,650);

	m_ObjectsCamera->push_back(m_Hero);
/*	m_ListBoss->push_back(m_SnakeMans);*/

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
	
	case DIK_C:
		m_Hero->ActiveSkill(0);
		break ;
	case DIK_F:
		m_Hero->ActiveSkill(1);
		break ;
	case DIK_E:
		m_Hero->ActiveSkill(2);
		break ;
	case DIK_R:
		m_Hero->ActiveSkill(3);
		break ;	
	case DIK_T:
		m_Hero->CallPet();
		break ;	
	case DIK_NUMPAD9:
		m_STT = FREEZETIME ;
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
	/*  Update Boss in camera                                             */
	/************************************************************************/	
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
	/*  Collision Special vs Object                                        */
	/************************************************************************/	
	for (std::vector<MyObject*>::iterator i = m_SpecialObject->begin();i!= m_SpecialObject->end();i++)
	{		
		for (std::vector<MyObject*>::iterator j = m_ObjectsCamera->begin();j!= m_ObjectsCamera->end();j++)
		{
			(*i)->ProcessCollision(*j);
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
	/************************************************************************/
	/*  Collision Object vs item                                            */
	/************************************************************************/
	for (std::vector<MyObject*>::iterator i = m_ListItem->begin();i!= m_ListItem->end();i++)
	{		
		for (std::vector<MyObject*>::iterator j = m_ObjectsCamera->begin();j!= m_ObjectsCamera->end();j++)
		{
			(*i)->ProcessCollision(*j);
		}		
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

	

		for (std::vector<MyObject*>::iterator i = m_SpecialObject->begin();i!= m_SpecialObject->end();i++)
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