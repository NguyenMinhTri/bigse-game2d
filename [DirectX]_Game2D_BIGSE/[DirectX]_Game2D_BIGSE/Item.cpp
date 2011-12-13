#include "Item.h"
#include "RSMainGame.h"
#include "Global.h"

Item::Item(void)
{
	Init();
}


Item::~Item(void)
{
}
void Item :: Init()
{
	m_effect = 2 ;
	m_STT = ACTIVE;
	m_Item = RSMainGame::get()->getMedicine();
	m_InfoSprite.setSize(52,63);
	setSize(52,63);
}
bool Item::iCollision(MyObject* _Obj){
	return false;
}


void Item::ProcessCollision(MyObject* _Obj)
{
	if(getRect().iCollision(_Obj->getRect()))
	{
	      _Obj->setHp(getHp() + 10 );
		
	}
}

void Item::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler,float x, float y)
{
// 	if(m_STT!=ACTIVE)
// 	{
// 		return;
// 	}
		m_InfoSprite.setXY(x,y);
		m_Item->Draw(_MWorld,m_InfoSprite,_Handler);
}
//vi object la abstract class nen ke' thua` hok xai` van~ fai? khai bao' ra day
void Item ::Animation(float _Time)
{
}
void Item::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	m_InfoSprite.setXY(m_X,m_Y);
	m_Item->Draw(_MWorld,m_InfoSprite,_Handler);
}
void Item ::UpdateStatus(float _Time)
{

}
void Item ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{

}
void Item :: Release()
{

}