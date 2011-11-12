#include "Skill.h"
#include "Global.h"
#include "RSMainGame.h"


Skill::Skill(void)
{
}


Skill::~Skill(void)
{
}

void Skill::Init(){
	m_Combo = 0;
	m_STT = READY;
	m_InfoSprite.setSize(300,200);
	m_SSkill = RSMainGame::get()->getCharacter();
}
void Skill::Active (float _X,float _Y,int _Dir)
{
	if (m_STT != ACTIVE) //chua tung skill
	{
		m_X = _X;
		m_Y = _Y;
		m_Dir = _Dir;
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

}

void Skill::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){

}

void Skill::Animation(float _Time)
{
	
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.15f)
		{
			m_TimeAni-= 0.15f;
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

void Skill::Update(float _Time){

}

void Skill::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Dir<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY(-125+m_X,-54+m_Y);
	m_SSkill->Draw(_MWorld,m_InfoSprite,_Handler);
}

void Skill::Release(){
}
	 