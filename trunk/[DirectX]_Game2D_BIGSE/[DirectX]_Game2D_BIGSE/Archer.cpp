#include "Archer.h"
#include "Character.h"
#include "RSMainGame.h"
#include "Global.h"
#include "Frenzy.h"
#include "CallPet.h"
#include "SkillArcher.h"
#include "Arrow.h"

Archer::Archer(void)
{
	arrow = false ;
	m_HP = 10; 
	m_Damage = 1;
}

Archer::~Archer(void)
{
}

void Archer ::ActiveSkill(int _Index){
		m_skillManager->ActiveSkill(_Index,m_X,m_Y,m_Dir);
		if (m_Vy < 0) //nhay len
		{
			m_Vy = fabs (m_Vy);
		}
}
void Archer ::Init()
{
	m_Archer= RSMainGame ::get()->getArcher();
	m_InfoSprite.setSize(300,200);
	m_STT = ACTIVE ;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new SkillArcher());
	m_skillManager->AddSkill(new Arrow());
	
}

bool Archer::iCollision(MyObject* _Obj){
	return false;
}
void Archer::ProcessCollision(MyObject* _Obj){
	m_skillManager->ProcessCollision(_Obj);
}

void Archer::Animation(float _Time){//1 walk,  2 jump, 3 alert, 4 hit, 5 skill
	m_TimeAni += _Time ;

	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;
			
			if(m_skillManager->getSkill(1)->getShoot() == true && m_skillManager->getSkill(1)->getSTT() ==ACTIVE)
			{
				m_InfoSprite.NextFrame(16,3);
			}
			else
			{
				if (m_Vy != 0 )
				{
					m_InfoSprite.NextFrame(4,3);
					if(m_InfoSprite.getCurFrame() >6)
					{
						m_InfoSprite.setCurFrame(4);
					}
				}
				else{
					if (m_Vx == 0){
						m_InfoSprite.NextFrame(8,4);
					} 
					else{
						m_InfoSprite.NextFrame(0,4);
					}
				}
			}
				
		}
		break;
	}
}
void Archer::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(getLife() == false)
	{
		return ;
	}

	m_skillManager->Draw(_MWorld,_Handler);

	if( getActive() ==false)
	{
		if (timeGetTime()%400 >200)
		{
			return ;
		}
	}

	if (m_skillManager->getSkill(0)->getSTT()==ACTIVE)
	{
		m_InfoSprite.setCurFrame(m_skillManager->getSkill(0)->getInfoSprite().getCurFrame());
	}

	if (m_Dir<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY(-125+m_X,-54+m_Y);

	m_Archer->Draw(_MWorld,m_InfoSprite,_Handler);

}

void Archer::UpdateStatus(float _Time)
{
	if(!m_iActive )
	{
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 1 )
		{
			m_iActive = true ;
			m_TimeUpdate =0;

		}
	}
}

void Archer::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	Move(_Time,_Terrain,_MaxWidth,_MaxHeight);	
	UpdateStatus(_Time);

	m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
}
void Archer::Release(){

}
void Archer::setMove(int _move){
	/*if(m_HIT->getSTT()!= ACTIVE){*/
	m_Vx = _move;
	m_Dir = _move;
	/*}*/
}
void Archer::setJump(){

	if ((m_Vy== 0) && (m_skillManager->getSkill(0)->getSTT()!= ACTIVE))
	{
		m_Vy = -1* g_VY_JUMP;
	}
}
