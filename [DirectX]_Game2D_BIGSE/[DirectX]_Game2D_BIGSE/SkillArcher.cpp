#include "SkillArcher.h"
#include "Skill.h"
#include "Global.h"
#include "RSMainGame.h"


SkillArcher::SkillArcher(void)
{
	Init();
}

SkillArcher::~SkillArcher(void)
{
}

void SkillArcher::Init(){
	m_Damage = 1;
	m_STT = READY;
    setSize(100,100);
	m_SSkill = RSMainGame::get()->getArcher();
}
void SkillArcher::Active (float _X,float _Y,int _Dir)
{	
	if(m_STT!=ACTIVE)
	{
		if (_Dir>0)
		{
			m_X = _X ;
			m_Y = _Y;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X + 50 - m_Width ;
			m_Y = _Y;
			m_Direct = _Dir;
		}
	
		m_InfoSprite.setCurFrame(12);
		m_TimeAni = 0;	
		m_STT = ACTIVE;
		m_iCollision = true;
	}
}

void SkillArcher::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			
				m_InfoSprite.NextFrame(12,4);
				if (m_InfoSprite.getCurFrame() >14)
				{				
					m_STT = READY;
					m_TimeAni =0;
				}
		}
	}
}
void SkillArcher::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){
	Animation(_Time);
	
}
// 
void SkillArcher::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY( m_X+200,m_Y);


}

void SkillArcher::Release()
{

}
