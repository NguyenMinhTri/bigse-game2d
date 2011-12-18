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
	m_iCollision = false;
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
		m_iCollision = false ;
	}
	
}

int Frenzy::getDamageEX(int _Damage, int _Offset)
{
	return _Damage+ rand()%_Offset;
}

void Frenzy::Animation(float _Time){
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.16f)
		{
			m_TimeAni-= 0.16f;
			m_InfoSprite.NextFrame(0,13);
			if(m_InfoSprite.getCurFrame() ==5)
			{
				m_iCollision = true;
			}
			if(m_InfoSprite.getCurFrame()>=12)
			{
					m_STT= COOLDOWN ;
					m_TimeAni=0;
			}
		}
	}
}

void Frenzy::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 4)
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
