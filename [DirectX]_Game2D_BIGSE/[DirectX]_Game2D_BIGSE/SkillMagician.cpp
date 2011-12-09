#include "SkillMagician.h"
#include "Global.h"
#include "RSMainGame.h"


SkillMagician::SkillMagician(void)
{
	Init();
}


SkillMagician::~SkillMagician(void)
{
}

void SkillMagician::Init(){
	m_Damage = 1;
	m_STT = READY;
	setSize(165,100);
	m_SSkill = RSMainGame::get()->getMagician();
}
void SkillMagician::Active (float _X,float _Y,int _Dir)
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
	}
}

void SkillMagician::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;

			m_InfoSprite.NextFrame(12,5);
			if (m_InfoSprite.getCurFrame() >15)
			{				
				m_STT = READY;
				m_TimeAni =0;
			}
		}
	}
}
void SkillMagician::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){
	Animation(_Time);

}

void SkillMagician::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY( m_X,m_Y);


}

void SkillMagician::Release()
{

}
