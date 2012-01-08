#include "Character.h"
#include "RSMainGame.h"
#include "Global.h"
#include "Frenzy.h"
#include "CallPet.h"
#include "SkillHit.h"
#include "Pet.h"
#include "Thunder.h"

Character::Character(void)
{
	m_HP = 20000 ; 
	Init();
}

Character::~Character(void)
{

}

void Character::ActiveSkill(int _Index){

	m_skillManager->ActiveSkill(_Index,m_X,m_Y,m_Direct);
}

void Character::Init(){
	m_SCharater = RSMainGame::get()->getCharacter();
	m_InfoSprite.setSize(300,200);
	m_InfoSprite.setDepth(0.2);
	setSize(50,85);

	m_STT = ACTIVE;
	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new SkillHit(this));
	m_skillManager->AddSkill(new Frenzy());
	m_skillManager->AddSkill(new Pet(this));
	m_skillManager->AddSkill(new Thunder());
}

bool Character::iCollision(MyObject* _Obj){
	return false;
}


void Character::ProcessCollision(MyObject* _Obj){
		m_skillManager->ProcessCollision(_Obj);
}

void Character::Animation(float _Time){
	m_TimeAni += _Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;

			if (m_Vy != 0){
				m_InfoSprite.setCurFrame(4);

			}else{
				if (m_VxDirect == 0){
					m_InfoSprite.NextFrame(8,4);
				} 
				else{
					m_InfoSprite.NextFrame(0,4);
				}
			}
		}
		break;
	}
		
}

void Character::UpdateStatus(float _Time)
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
	 if(getFrenzy() == true)
	 {
		 m_TimeUpdate += _Time;
		 if(m_TimeUpdate > 1.95)
		 {
			 setFrenzey(false);
			 m_TimeUpdate =0;
		 }
	 }
	 if(m_iThunder== true)
	 {
		 m_TimeUpdate += _Time;
		 if(m_TimeUpdate > 0.5)
		 {
			 m_iThunder =false ;
			 m_TimeUpdate =0;
		 }
	 }
}

void Character::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	if(getFrenzy() == false )
	{
		Move(_Time,_Terrain,_MaxWidth,_MaxHeight);	
	}
	UpdateStatus(_Time);
	m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
}
void Character::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(m_iThunder ==false)
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

		if (m_Direct<0){
			m_InfoSprite.setScaleX(1);
		}else{
			m_InfoSprite.setScaleX(-1);
		}
		m_InfoSprite.setXY(-125+m_X,-54+m_Y);

		m_SCharater->Draw(_MWorld,m_InfoSprite,_Handler);
	}
		
}

void Character::Release(){

}

