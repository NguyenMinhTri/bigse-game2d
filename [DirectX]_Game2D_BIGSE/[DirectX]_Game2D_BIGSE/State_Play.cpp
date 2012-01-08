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

	m_ListItem = ManagerObject::Instance()->getListItem();
	m_ObjectsCamera = ManagerObject::Instance()->getObjects();
	m_ListMonster = ManagerObject::Instance()->getListMonster();
	m_ListEffect = ManagerObject::Instance()->getListEffect();
	m_ListBoss = ManagerObject::Instance()->getListBoss();
	m_SpecialObject = ManagerObject::Instance()->getSpecialObjects();

	D3DXCreateSprite(m_Device,&m_Handle);

	m_Camera = new Camera(0,0,g_SCREEN_WIDTH,g_SCREEN_HEIGHT);
#pragma region Init Item


#pragma region Init Character   

	std::vector<MyObject*>::iterator u = m_ObjectsCamera->begin();
	m_Hero= (Character*)(*u);



#pragma endregion Init Character

#pragma region Init Map Terrain



	m_QuadTree = ManagerObject::Instance()->getQuadTree();	

	m_Map = ManagerObject::Instance()->getMap();
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
	
	case DIK_H:
		m_Hero->ActiveSkill(0);
		break ;
	case DIK_J:
		m_Hero->ActiveSkill(1);
		break ;
	case DIK_K:
		m_Hero->ActiveSkill(2);
		break ;
	case DIK_U:
		m_Hero->ActiveSkill(3);
		break ;	
	case DIK_T:	
		break ;	
	case DIK_NUMPAD9:
		m_STT = FREEZETIME ;
		break;
	case DIK_S:
		for (std::vector<MyObject*>::iterator i = m_SpecialObject->begin();i!= m_SpecialObject->end();i++)
		{
			CRECT r1 = m_Hero->getRect();
			CRECT r2 =(*i)->getRect();
			bool is = r1.iCollision(r2);
			if (is)
			{

				int  id1 = (*i)->getID();
				int id2;
				if(id1%2 ==0)id2= id1+1;
				else id2 = id1-1;
				
				for (std::vector<MyObject*>::iterator f = m_SpecialObject->begin();f!= m_SpecialObject->end();f++)
				{
					if ((*f)->getID()==id2)
					{
						m_Hero->setXY((*f)->getX(),(*f)->getY()-40);
						return;
					}
				}
				

			}

		}

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

	
	if (m_Hero->m_skillManager->getSkill(3)->getSTT()==ACTIVE)
	{
		m_Camera->UpdateEffect(_Time);
	} 
	else
	{
		bool iflag = false;
		for (std::vector<MyObject*>::iterator i = m_ListBoss->begin();i!= m_ListBoss->end();i++)
		{	
			Character* b = (Character*)(*i);
			if (b->getRect().iCollision(m_Camera->getRect()) && b->getLife()==true)
			{
				for (int j=0;j<4;j++)
				{
					if(b->m_skillManager->getSkill(j)->getSTT()==ACTIVE)
					{
						m_Camera->UpdateEffect(_Time);
						iflag = true;
						break;
					}
				}
			}
			
			if(iflag) break;
		}
		if (iflag==false)
		{
			m_Camera->NoEffect();
		}
	}
	
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
// 		if( (*i)->getLife() == false)
// 		{
// 			(*i)->Release();
// 			i = m_ObjectsCamera->erase(i);
// 			continue;
// 		}
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
	for (std::vector<MyObject*>::iterator i = m_ListItem->begin();i!= m_ListItem->end();i++)
	{		
		for (std::vector<MyObject*>::iterator j = m_ObjectsCamera->begin();j!= m_ObjectsCamera->end();j++)
		{
			(*i)->ProcessCollision(*j);
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
		
		
		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);
}
void State_Play::Release()
{

}