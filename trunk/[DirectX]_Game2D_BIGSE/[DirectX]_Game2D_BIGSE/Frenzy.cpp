#include "Frenzy.h"
#include "Global.h"
#include "RSMainGame.h"

Frenzy::Frenzy(void)
{
	Init();
}
Frenzy::~Frenzy(void)
{
}
void Frenzy::Init(){
	m_Damage = 1;
	m_Combo = 0;
	m_STT = READY;
	m_InfoSprite.setSize(435,419);

	setSize(435,419);
	m_SSkill = RSMainGame::get()->getFrenzy();
}

void Frenzy::Active (float _X,float _Y,int _Dir)
{
	if (m_STT == READY) //chua tung Frenzy
	{
		if (_Dir>0)
		{
			m_X = _X  + 50;
			m_Y = _Y-(394-85);
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X -m_Width ;
			m_Y = _Y-(394-85);
			m_Direct = _Dir;
		}

		m_STT = ACTIVE;
		m_InfoSprite.setCurFrame(0);	
		m_TimeAni = 0;

	}
	
}

bool Frenzy::iCollision (MyObject* _Obj) {
	return false;
}

void Frenzy::ProcessCollision(MyObject* _Obj){
	if ( m_STT!= ACTIVE ) 
	{
		return;
	}
	if(!getRect().iCollision(_Obj->getRect()))
	{
		return ;
	}
	else {
		if(_Obj->getActive() == false )
		{
			return ;
		}//true la chua trung
		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - getDamage()  );
		if(_Obj->getHp() == 0)
		{
			_Obj->setLife(false); 
		}		
	}
}



int Frenzy::getDamageEX(int _Damage, int _Offset)
{
	return _Damage+ rand()%_Offset;
}

void Frenzy::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){

}

void Frenzy::Animation(float _Time){
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.16f)
		{
			m_TimeAni-= 0.16f;
			m_InfoSprite.NextFrame(0,12);
			if(m_InfoSprite.getCurFrame()>12)
			{
					m_STT=READY;
					m_TimeAni=0;
			}
		}
	}
}
void Frenzy::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case ACTIVE:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 1)
		{
			m_STT = COOLDOWN;
			m_TimeUpdate = 0;
		}
		break;
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 2)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
	

}

void Frenzy::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){
	Animation(_Time);
	
	UpdateStatus(_Time);
}

void Frenzy::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY(m_X,m_Y);
	m_SSkill->Draw(_MWorld,m_InfoSprite,_Handler);

}

void Frenzy::Release(){
}
