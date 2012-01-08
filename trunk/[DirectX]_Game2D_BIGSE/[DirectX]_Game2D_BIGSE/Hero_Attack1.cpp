#include "Hero_Attack1.h"
#include "EffectSystem.h"
#include "ManagerObject.h"
#include "Hero_Effect1.h"
#include "EffectFont.h"
#include "SoundGame.h"

Hero_Attack1::Hero_Attack1(Hero* _Hero)
{
	m_Hero=_Hero;
	Init();
}


Hero_Attack1::~Hero_Attack1(void)
{
}

void Hero_Attack1::Init()
{

	m_TestBallFly=false;
	m_VBallFly=100;
	m_iCollision=false;
	m_Damage = 3000;

	m_STT = READY;
	setSize(415,100);
	m_Hero_Attack1Sprite = RSMainGame::get()->getHero_Attack1();
	m_Hero_Attack1_BallSprite = RSMainGame::get()->getHero_Attack1_Ball();

	m_Hero_Attack1_BallInfoSprite.setDepth(0.3f);
	m_Hero_Attack1_BallInfoSprite.setSize(415,143);
	m_Hero_Attack1InfoSprite.setSize(570,255);
	m_Hero_Attack1InfoSprite.setDepth(0.3f);
}
void Hero_Attack1::Active(float _X,float _Y,int _Dir)
{
	for(int i=0;i<4;i++)
	{
		if(m_Hero->m_skillManager->getSkill(i)->getSTT()==ACTIVE)
			return;
	}
	if (m_STT == READY) //chua tung skill
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

		m_Hero_Attack1InfoSprite.setCurFrame(0);
		m_Hero_Attack1_BallInfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
	}
}
void Hero_Attack1::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		SoundGame ::Instance()->PlayBeam_Fire();
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_Hero_Attack1InfoSprite.NextFrame(0,15);			
			if(m_Hero_Attack1InfoSprite.getCurFrame()>=8)
			{
				
				m_VBallFly+=100;
				m_Hero_Attack1_BallInfoSprite.NextFrame(0,4);
				m_TestBallFly=true;
				m_iCollision=true;
				if(m_Hero_Attack1_BallInfoSprite.getCurFrame()>=3)
				{
					m_TestBallFly=false;
					m_VBallFly=100;

				}
			}
			if(m_Hero_Attack1InfoSprite.getCurFrame()>=14)
			{
				m_STT=COOLDOWN;
				m_TimeAni=0;
			}


		}
	}
}


void Hero_Attack1::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 20)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}


}

void Hero_Attack1::ProcessCollision(MyObject *_Obj)
{
	
	if(getiCollision() == true )
	{
		CRECT r;
		r.Left =m_Hero_Attack1_BallInfoSprite.getX();
		r.Top = m_Hero_Attack1_BallInfoSprite.getY() ;
		r.Right = r.Left+ 415;
		r.Bottom = r.Top  + 143;
		CRECT r1;
		r1.Left =m_Hero_Attack1InfoSprite.getX(); ;
		r1.Top = m_Hero_Attack1InfoSprite.getY() ;
		r1.Right = r1.Left+570;
		r1.Bottom = r1.Top  + 255 ;
		if(r.iCollision(_Obj->getRect())== true ||r1.iCollision(_Obj->getRect())== true)
		{
			if(_Obj->getActive() == false  )
			{
				return ;
			}//true la chua trung

			EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
			ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
			if (m_Direct<0)
			{
				Hero_Effect1 *m_HeroEffect1 = new Hero_Effect1(_Obj->getX()+20,_Obj->getY()+50);
				m_HeroEffect1->m_InfoSprite.setScaleX(1);
				m_HeroEffect1->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2-25,r.Top);
				ManagerObject::Instance()->getListEffect()->push_back(m_HeroEffect1);
			}
			else
			{
				Hero_Effect1 *m_HeroEffect1 = new Hero_Effect1(_Obj->getX()+130,_Obj->getY()+50);
				m_HeroEffect1->m_InfoSprite.setScaleX(-1);
				m_HeroEffect1->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2+25,r.Top);
				ManagerObject::Instance()->getListEffect()->push_back(m_HeroEffect1);
			}

			_Obj->setActive(false);
			_Obj->setFrenzey(true);
			_Obj->setHp(_Obj->getHp() - getDamage());
			if(_Obj->getHp() <= 0)
			{
				_Obj->setLife(false); 
			}	
		}
		
	}
}


void Hero_Attack1::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void Hero_Attack1::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_Hero_Attack1InfoSprite.setScaleX(1);
		m_Hero_Attack1_BallInfoSprite.setScaleX(1);
		m_Hero_Attack1_BallInfoSprite.setXY(m_X-100-m_VBallFly,m_Y-30);
		m_Hero_Attack1InfoSprite.setXY(m_X-15,m_Y-67);

	}else{
		m_Hero_Attack1InfoSprite.setScaleX(-1);
		m_Hero_Attack1_BallInfoSprite.setScaleX(-1);
		m_Hero_Attack1_BallInfoSprite.setXY(m_X+100+m_VBallFly,m_Y-30);
		m_Hero_Attack1InfoSprite.setXY(m_X-150,m_Y-67);

	}



	if(m_STT==ACTIVE)
	{
		m_Hero_Attack1Sprite->Draw(_mtWorld,m_Hero_Attack1InfoSprite,_Handler);
		if(m_TestBallFly==true)
		{
			m_Hero_Attack1_BallSprite->Draw(_mtWorld,m_Hero_Attack1_BallInfoSprite,_Handler);

		}

	}
}
