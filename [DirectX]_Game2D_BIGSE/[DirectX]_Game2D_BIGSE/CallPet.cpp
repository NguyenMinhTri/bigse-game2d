#include "CallPet.h"
#include "Global.h"
#include "RSMainGame.h"
#include "ManagerObject.h"
#include "EffectFont.h"
#include "EffectHit.h"
#include "SoundGame.h"
CallPet::CallPet(void)
{
	Init();
}
CallPet::~CallPet(void)
{
}
void CallPet::Init()
{
	
	m_Damage = 1500;
	m_STT = READY;
	m_InfoSprite.setSize(520,385);
	setSize(520,385);
	m_SSkill = RSMainGame::get()->getPet();
}

void CallPet::Active (float _X,float _Y,int _Dir)
{
	if (m_STT == READY) 
	{
		if (_Dir>0)
		{
			m_X = _X ;
			m_Y = _Y - 250;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X  - 400;
			m_Y = _Y -250;	
			m_Direct = _Dir;
		}

		m_STT = ACTIVE;
		m_InfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
	}
}

void CallPet::Animation(float _Time){
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.07f)
		{
			m_TimeAni-= 0.07f;
			m_InfoSprite.NextFrame(0,34);
			if(m_InfoSprite.getCurFrame() >=28 && m_InfoSprite.getCurFrame() <=30 )
			{
					SoundGame ::Instance()->PlayXetXet();
				m_iCollision= true;
			}
			if(m_InfoSprite.getCurFrame() == 33)
			{	
				m_STT=COOLDOWN;
				m_TimeAni=0;
			}
		}
	}
}

void CallPet::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 10)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}

void CallPet ::ProcessCollision(MyObject *_Obj)
{
	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}


		EffectHit* m_Effecthit = new EffectHit(m_X,m_Y - 30);
		ManagerObject::Instance()->getListEffect()->push_back(m_Effecthit);

		EffectFont* m_EffectFont = new EffectFont(m_X,m_Y - 30,m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - m_Damage );
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}

void CallPet::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}

void CallPet::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY(m_X,m_Y);
	m_SSkill->Draw(_MWorld,m_InfoSprite,_Handler);
}

void CallPet::Release()
{
}
