#include "Hero_Attack3.h"
#include "EffectSystem.h"
#include "ManagerObject.h"
#include "Hero_Effect2.h"
#include "EffectFont.h"
Hero_Attack3::Hero_Attack3(Hero* _Hero)
{
	m_Hero=_Hero;
	Init();
}


Hero_Attack3::~Hero_Attack3(void)
{
}

void Hero_Attack3::Init()
{

	m_TestBallFly=false;
	m_VBallFly=30;
	m_iCollision=false;
	m_Damage = 4000;

	m_STT = READY;
	setSize(97,150);
	m_Hero_Attack3Sprite = RSMainGame::get()->getHero_Attack3();
	m_Hero_Attack3_BallSprite = RSMainGame::get()->getHero_Attack3_Ball();
	m_Hero_Attack3_BallInfoSprite.setDepth(0.3f);
	m_Hero_Attack3_BallInfoSprite.setSize(97,150);
	m_Hero_Attack3InfoSprite.setSize(270,231);
	m_Hero_Attack3InfoSprite.setDepth(0.3f);

}
void Hero_Attack3::Active(float _X,float _Y,int _Dir)
{
	for(int i=0;i<4;i++)
	{
		if(m_Hero->m_skillManager->getSkill(i)->getSTT()==ACTIVE)
			return;
	}
	if (m_STT == READY&&m_Hero->getVY()==0) //chua tung skill
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

		m_Hero_Attack3InfoSprite.setCurFrame(0);
		m_Hero_Attack3_BallInfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
	}
}
void Hero_Attack3::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_Hero_Attack3InfoSprite.NextFrame(0,19);			
			if(m_Hero_Attack3InfoSprite.getCurFrame()>=15)
			{
				m_iCollision=true;
				m_VBallFly+=30;
				m_Hero_Attack3_BallInfoSprite.NextFrame(0,6);
				m_TestBallFly=true;
				if(m_Hero_Attack3_BallInfoSprite.getCurFrame()>=4)
				{
					m_TestBallFly=false;
					m_VBallFly=30;
				}
			}
			if(m_Hero_Attack3InfoSprite.getCurFrame()>=18)
			{
				m_STT=COOLDOWN;
				m_TimeAni=0;
			}


		}
	}
}


void Hero_Attack3::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
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

void Hero_Attack3::ProcessCollision(MyObject *_Obj)
{
	CRECT r;
	r.Left =m_Hero_Attack3_BallInfoSprite.getX(); ;
	r.Top = m_Hero_Attack3_BallInfoSprite.getY() ;
	r.Right = r.Left+ 97;
	r.Bottom = r.Top  + 150;
	CRECT r1;
	r1.Left =m_Hero_Attack3InfoSprite.getX(); ;
	r1.Top = m_Hero_Attack3InfoSprite.getY() ;
	r1.Right = r1.Left+270;
	r1.Bottom = r1.Top  + 231 ;
	if(getiCollision() == true &&( r.iCollision(_Obj->getRect())== true ||r1.iCollision(_Obj->getRect())== true ))
	{

		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung
		EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
			if (m_Direct<0)
			{
				Hero_Effect2 *m_HeroEffect2 = new Hero_Effect2(_Obj->getX()+20,_Obj->getY()+50);
				m_HeroEffect2->m_InfoSprite.setScaleX(1);
				m_HeroEffect2->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2-25,r.Top);
				ManagerObject::Instance()->getListEffect()->push_back(m_HeroEffect2);
			}
			else
			{
				Hero_Effect2 *m_HeroEffect2 = new Hero_Effect2(_Obj->getX()+130,_Obj->getY()+50);
				m_HeroEffect2->m_InfoSprite.setScaleX(-1);
				m_HeroEffect2->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2+25,r.Top);
				ManagerObject::Instance()->getListEffect()->push_back(m_HeroEffect2);
			}
		




		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - getDamage());
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}


void Hero_Attack3::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void Hero_Attack3::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_Hero_Attack3InfoSprite.setScaleX(1);
		m_Hero_Attack3_BallInfoSprite.setScaleX(1);
		m_Hero_Attack3_BallInfoSprite.setXY(m_Hero_Attack3InfoSprite.getX()-30-m_VBallFly,m_Y-60);
		m_Hero_Attack3InfoSprite.setXY(m_X-110,m_Y-105);

	}else{
		m_Hero_Attack3InfoSprite.setScaleX(-1);
		m_Hero_Attack3_BallInfoSprite.setScaleX(-1);
		m_Hero_Attack3_BallInfoSprite.setXY(m_Hero_Attack3InfoSprite.getX()+30+2*m_VBallFly,m_Y-60);
		m_Hero_Attack3InfoSprite.setXY(m_X-40,m_Y-105);

	}



	if(m_STT==ACTIVE)
	{
		m_Hero_Attack3Sprite->Draw(_mtWorld,m_Hero_Attack3InfoSprite,_Handler);
		if(m_TestBallFly==true)
		{
			m_Hero_Attack3_BallSprite->Draw(_mtWorld,m_Hero_Attack3_BallInfoSprite,_Handler);

		}

	}
}
