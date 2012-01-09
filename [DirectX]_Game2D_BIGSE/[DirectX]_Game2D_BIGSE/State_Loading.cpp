#include "State_Loading.h"
#include "ManagerObject.h"
#include "State_Play.h"


State_Loading::State_Loading(iPlay* GamePlay,LPCTSTR _fileMap,int _IDHero)
	:iState(GamePlay)
{
	m_ID = LOADING;
	m_IDHero = _IDHero;
	m_fileMap = _fileMap;
	m_Loading1=new Sprite(m_Device,"data\\image\\loading1.png",316,80,1);
	m_Loading3=new Sprite(m_Device,"data\\image\\loading3.png",316,80,1);
	m_Loading2=new Sprite(m_Device,"data\\image\\loading2.png",316,80,1);
	m_Tex = m_Loading2->GetImage();
}


State_Loading::~State_Loading(void)
{
}

void State_Loading::IsKeyDown(int KeyCode)
{

}
void State_Loading::OnKeyDown(int KeyCode)
{

}
void State_Loading::OnKeyUp(int KeyCode)
{

}

void State_Loading::Init()
{
	D3DXCreateSprite(m_Device,&m_Handle);
	m_Percent = 00;
}
void State_Loading::Update(float _Time)
{
	if (m_Percent==0)
	{	
		m_Percent=10;
		Draw();
		return;
	}
	if (m_Percent==10)
	{
		RSMainGame::get();	
		m_Percent=50;
		Draw();
		return;
	}
	if (m_Percent==50)
	{
		m_Percent=60;
		m_ListItem = new std::vector<MyObject*>();
		m_ObjectsCamera = new std::vector<MyObject*>();
		m_ListMonster = new std ::vector<MyObject*>();
		m_ListEffect = new std::vector<EffectSystem*>();
		m_ListBoss = new std ::vector<MyObject*>();
		m_SpecialObject =new std ::vector<MyObject*>();
		Draw();
		return;
	}

	if (m_Percent==60)
	{
		m_Percent=70;
		ManagerObject::Instance()->setListObject(m_ListItem);
		ManagerObject::Instance()->setObjects(m_ObjectsCamera);
		ManagerObject::Instance()->setListEffect(m_ListEffect);
		ManagerObject::Instance()->setListMonster(m_ListMonster);
		ManagerObject::Instance()->setListBoss(m_ListBoss);
		ManagerObject::Instance()->setSpecialObjects(m_SpecialObject);
		Draw();
		return;
	}

	if (m_Percent ==70)
	{
		m_Percent=80;
		m_LoadMap = new LoadMap();
		m_LoadMap->LoadMapFormFile(m_fileMap,m_Device);

		int m = m_LoadMap->m_Width > m_LoadMap->m_Height ? m_LoadMap->m_Width : m_LoadMap->m_Height;

		m_QuadTree = new QuadTree(CRECT(0,m*50,0,50*m));
		ManagerObject::Instance()->setQuadTree(m_QuadTree);
		Draw();
		return;
	}
	if (m_Percent==80)
	{
		if (m_IDHero==0)
		{
			Character* hero = new Character();
			hero->setXY(500,0);
			m_ObjectsCamera->push_back(hero);
		} 
		else
		{
			if (m_IDHero==1)
			{
				Character* hero = new Angle();
				hero->setXY(500,0);
				m_ObjectsCamera->push_back(hero);
			} 
			else
			{
				Character* hero = new Hero();
				hero->setXY(500,0);
				m_ObjectsCamera->push_back(hero);
			}
		}

		m_LoadMap->TranslateMap();
		m_Map = new Terrain(m_LoadMap->m_Terrain,m_LoadMap->m_TerrainExtends,m_LoadMap->m_Width,m_LoadMap->m_Height);
		ManagerObject::Instance()->setMap(m_Map);
		m_Percent=100;
		Draw();
		return;
	}
	
	if (m_Percent==100)
	{
		m_iPlay->SetNextState(new State_Play (this->m_iPlay));
		return;
	}
	
}
void State_Loading::Draw()
{	
	rect.top=0;
	rect.bottom=52;
	rect.left = (100-m_Percent)*300/100;
	rect.right = rect.left + m_Percent*300/100;
	m_Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);

	if(m_Device->BeginScene())
	{
		m_Handle->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK|D3DXSPRITE_ALPHABLEND);

		m_Loading1->Draw(354,400,0,m_Handle);
		m_Handle->Draw(m_Tex,&rect,NULL,&D3DXVECTOR3(362,408,0.0f),D3DCOLOR_ARGB(255,255,255,255));
		m_Loading3->Draw(354,400,0,m_Handle);
		m_Handle->End();
		m_Device->EndScene();
	}
	m_Device->Present(NULL,NULL,NULL,NULL);

}
void State_Loading::Release()
{
	if (m_Handle!=NULL)
	{
		m_Handle->Release();
		m_Handle = NULL;
	}
	if (m_Loading1!= NULL)
	{
		m_Loading1->Release();
		delete m_Loading1;
		m_Loading1 = NULL;
	}
	if (m_Loading2!= NULL)
	{
		m_Loading2->Release();
		delete m_Loading2;
		m_Loading2 = NULL;
	}
	if (m_Loading3!= NULL)
	{
		m_Loading3->Release();
		delete m_Loading3;
		m_Loading3 = NULL;
	}
	
}