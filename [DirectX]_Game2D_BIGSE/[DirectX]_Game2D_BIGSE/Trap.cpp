#include "Trap.h"
#include "RSMainGame.h"
#include "EffectFont.h"
#include "ManagerObject.h"
Trap::Trap(void)
{
	Init() ;
}


Trap::~Trap(void)
{
}
void Trap ::Init()
{
	m_Damage = 100;
	m_Trap = RSMainGame::get()->getTrap() ;
	m_InfoTrap.setSize(72,43);
	setSize(50,40);
}

void Trap ::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	m_InfoTrap.setXY(m_X,m_Y + 10 );
	m_Trap->Draw(_MWorld,m_InfoTrap,_Handler) ;
}

void Trap ::ProcessCollision(MyObject* _Obj) 
{
	if(getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}
		EffectFont* m_EffectFont = new EffectFont(m_X,m_Y ,m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - m_Damage );
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}

bool Trap ::iCollision(MyObject* _Obj){return false ;}
void Trap ::Animation(float _Time){}
void Trap ::UpdateStatus(float _Time){}
void Trap ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){}
void Trap ::Release(){}
