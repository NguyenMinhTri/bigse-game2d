#include "Skill.h"
#include "Global.h"
#include "RSMainGame.h"


Skill::Skill(void)
{
	//m_ID = ;
	Init();
}


Skill::~Skill(void)
{
}

void Skill::Init(){
	m_Damage = 1;
	m_Combo = 0;
	m_STT = READY;
	setSize(150,150);
	m_SSkill = RSMainGame::get()->getCharacter();
}
void Skill::Active (float _X,float _Y,int _Dir)
{
	if (m_STT != ACTIVE) //chua tung skill
	{
		if (_Dir>0)
		{
			m_X = _X;
			m_Y = _Y;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X + 50- m_Width ;
			m_Y = _Y;
			m_Direct = _Dir;
		}
		
		m_STT = ACTIVE;
		m_InfoSprite.setCurFrame(12);
		m_Combo = 0;
		m_NextCombo = false;
		m_TimeAni = 0;

	}
	else // dang skill
	{
		switch(m_Combo)
		{
		case 0:
			if (m_InfoSprite.getCurFrame()==14)
			{
				m_NextCombo = true;
			}
			break;
		case 1:
			if (m_InfoSprite.getCurFrame()==18){
				m_NextCombo = true;
			}
			break;
		case 2:
			if (m_InfoSprite.getCurFrame()==22){
				m_NextCombo = true;
			}
			break;
		}
	}

}

bool Skill::iCollision (MyObject* _Obj) {
	return false;
}

void Skill::ProcessCollision(MyObject* _Obj){
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



int Skill::getDamageEX(int _Damage, int _Offset)
{
	return _Damage+ rand()%_Offset;
}

void Skill::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{

}

void Skill::Animation(float _Time)
{
	
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			switch(m_Combo)
			{
			case 0:
				m_InfoSprite.NextFrame(12,4);
				if (m_InfoSprite.getCurFrame()>14)
				{
					if (m_NextCombo)
					{
						m_Combo=1;
						m_InfoSprite.setCurFrame(16);
						m_NextCombo = false;
						m_TimeAni = 0;
					}
					else
					{
						m_STT = READY;
					}					
				}
				break;
			case 1:
				m_InfoSprite.NextFrame(16,4);
				if (m_InfoSprite.getCurFrame()>18) {
					if (m_NextCombo){
						m_InfoSprite.setCurFrame(20);
						m_Combo=2;
						m_NextCombo = false;
						m_TimeAni = 0;
					}else{
						m_STT = READY;
					}					
				}
				break;

			case 2:
				m_InfoSprite.NextFrame(20,4);
				if (m_InfoSprite.getCurFrame()>22) {
					if (m_NextCombo){
						m_Combo=3;
						m_InfoSprite.setCurFrame(24);
						m_NextCombo = false;
						m_TimeAni = 0;
					}else{
						m_STT = READY;
					}					
				}
				break;

			case 3:
				m_InfoSprite.NextFrame(24,5);
				if (m_InfoSprite.getCurFrame()>27) {
					
						m_Combo = 0;
						m_NextCombo = false;					
						m_STT = READY;	
						m_InfoSprite.setCurFrame(12);
						m_TimeAni = 0;
				}
				break;

			}					
		}
	}
}

void Skill::UpdateStatus(float _Time){

}

void Skill::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){
	Animation(_Time);
	UpdateStatus(_Time);
}

void Skill::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY(m_X,m_Y);
/*	m_SSkill->Draw(_MWorld,m_InfoSprite,_Handler);*/

}

void Skill::Release(){
}
	 