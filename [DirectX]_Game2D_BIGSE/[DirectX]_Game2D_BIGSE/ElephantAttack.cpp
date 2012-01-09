#include "ElephantAttack.h"
#include "RSMainGame.h"
#include "Monster.h"
#include "EffectFont.h"
#include "ManagerObject.h"
#include "EffectInfoEle.h"
ElephantAttack::ElephantAttack()
{
	Init() ;
}


ElephantAttack::~ElephantAttack(void)
{

}
ElephantAttack::ElephantAttack(Character *_Character)
{
	m_Character = _Character ;
	Init() ;
}
void ElephantAttack ::Init()
{
	m_iCollision = false;
	m_Damage = 300;

	m_STT = READY;
	m_InfoSprite.setSize(195,193);

	setSize(170,193);
	m_Attack = RSMainGame::get()->getElephantAttack();
}

void ElephantAttack::Active (float _X,float _Y,int _Dir)
{
	if (m_STT == READY) //chua tung Frenzy
	{
		if (_Dir>0)
		{
			m_X = _X  ;
			m_Y = _Y;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X ;
			m_Y = _Y;
			m_Direct = _Dir;
		}

		m_STT = ACTIVE;
		m_InfoSprite.setCurFrame(0);	
		m_TimeAni = 0;
		m_iCollision = false ;
	}
}

void ElephantAttack ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung
		EffectInfoEle *_EffectInfo = new EffectInfoEle (_Obj->getX(), _Obj->getY());
		ManagerObject::Instance()->getListEffect()->push_back(_EffectInfo);

		EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
		_Obj->setActive(false);

		_Obj->setHp(_Obj->getHp() - m_Damage);
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}

void ElephantAttack::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_InfoSprite.NextFrame(0,12);
			if(m_InfoSprite.getCurFrame() >=2 && m_InfoSprite.getCurFrame() <=8)
			{
				m_iCollision = true;
			}
			if(m_InfoSprite.getCurFrame()>=11)
			{
				m_STT= COOLDOWN ;
				m_TimeAni=0;
			}
		}
	}
}

void ElephantAttack::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 2.0f)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}
void ElephantAttack::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){
	Animation(_Time);	
	UpdateStatus(_Time);
}
void ElephantAttack::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
		m_InfoSprite.setXY(m_X - 30 ,m_Y - 25);
	}else{
		m_InfoSprite.setScaleX(-1);
		m_InfoSprite.setXY(m_X ,m_Y - 25);
	}
	m_Attack->Draw(_MWorld,m_InfoSprite,_Handler);
}
void ElephantAttack ::Release()
{

}