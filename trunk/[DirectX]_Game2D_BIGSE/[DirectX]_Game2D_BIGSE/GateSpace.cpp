#include "GateSpace.h"
#include "RSMainGame.h"
#include "Global.h"

GateSpace::GateSpace(int _Direction)
{
	m_HP = 1000000000;
	m_Direct = _Direction ;
	Init();
}


GateSpace::~GateSpace(void)
{

}
void GateSpace :: Init()
{
	m_InfoSprite.setSize(300,180) ;
	setSize(50,180);
	m_InfoSprite.setDepth(0.2);
	m_SpaceGate = RSMainGame ::get()->getSpaceGate() ;
	m_STT = ACTIVE ;
}
bool GateSpace ::iCollision(MyObject* _Obj)
{
	return false;
}
void  GateSpace ::ProcessCollision(MyObject* _Obj)
{
	if(getRect().iCollision(_Obj->getRect()))
	{
		if(m_Direct ==-1)
		{
		   _Obj->setXY(1250 + 300,_Obj->getY());
		}
		if(m_Direct ==1)
		{
			
		}
	}
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
	}
	if(m_Direct == 1)
	{
		m_InfoSprite.setScaleX(1);
	}
	m_InfoSprite.setXY(m_X,m_Y - 120);
	m_SpaceGate->Draw(_MWorld,m_InfoSprite,_Handler);
}
void GateSpace ::Release()
{

}