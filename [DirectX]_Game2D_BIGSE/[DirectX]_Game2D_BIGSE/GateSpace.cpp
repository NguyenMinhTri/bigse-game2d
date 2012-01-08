#include "GateSpace.h"
#include "RSMainGame.h"
#include "Global.h"


GateSpace::GateSpace(int _ID)
{
	m_HP = 1000000000;
	m_ID = _ID;
	
	if ((m_ID%2)==0)
	{
		m_Direct =1;
	}
	else
	{
		m_Direct = -1;
	}
	Init();
	m_iActive = false;
}


GateSpace::~GateSpace(void)
{

}
void GateSpace :: Init()
{
	m_InfoSprite.setSize(300,180) ;
	setSize(100,180);
	m_InfoSprite.setDepth(0.58f);
	m_SpaceGate = RSMainGame ::get()->getSpaceGate() ;
	m_STT = ACTIVE ;
}
bool GateSpace ::iCollision(MyObject* _Obj)
{
	return false;
}
void  GateSpace ::ProcessCollision(MyObject* _Obj)
{
	
}
void GateSpace ::Animation(float _Time)
{
	m_TimeAni += _Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			m_InfoSprite.NextFrame(0,5);
		}
		break;
	}
}
void GateSpace ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
}
void GateSpace ::UpdateStatus(float _Time)
{

}
void GateSpace ::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(m_Direct == -1)
	{
		m_InfoSprite.setScaleX(-1);
		m_InfoSprite.setXY(m_X,m_Y - 120);
	}
	if(m_Direct == 1)
	{
		m_InfoSprite.setScaleX(1);
		m_InfoSprite.setXY(m_X-150,m_Y - 120);
	}	
	m_SpaceGate->Draw(_MWorld,m_InfoSprite,_Handler);
}
void GateSpace ::Release()
{

}