#include "SnakeMens_Attack2.h"
#include "EffectSystem.h"
#include "ManagerObject.h"
#include "SnakeMens_Effect2.h"
#include "EffectFont.h"
#include "EffectFrenzy.h"
SnakeMens_Attack2::SnakeMens_Attack2(SnakeMans* _SnakeMens)
{
	m_SnakeMens=_SnakeMens;
	Init();
}


SnakeMens_Attack2::~SnakeMens_Attack2(void)
{
}

void SnakeMens_Attack2::Init()
{

	m_TestBallFly=false;
	m_VBallFly=100;
	m_iCollision=false;
	m_Damage = 2000;

	m_STT = READY;
	setSize(415,100);
	m_SnakeMens_Attack2Sprite = RSMainGame::get()->getSnakeMans_Attack2();
	m_SnakeMens_Attack2_BallSprite = RSMainGame::get()->getSnakeMans_Attack2_Ball();

	m_SnakeMens_Attack2_BallInfoSprite.setDepth(0.3f);
	m_SnakeMens_Attack2_BallInfoSprite.setSize(415,143);
	m_SnakeMens_Attack2InfoSprite.setSize(570,255);
	m_SnakeMens_Attack2InfoSprite.setDepth(0.3f);
}
void SnakeMens_Attack2::Active(float _X,float _Y,int _Dir)
{
	for(int i=0;i<4;i++)
	{
		if(m_SnakeMens->m_skillManager->getSkill(i)->getSTT()==ACTIVE)
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

		m_SnakeMens_Attack2InfoSprite.setCurFrame(0);
		m_SnakeMens_Attack2_BallInfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
		m_TestBallFly=false;
	}
}
void SnakeMens_Attack2::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_SnakeMens_Attack2InfoSprite.NextFrame(0,25);			
			if(m_SnakeMens_Attack2InfoSprite.getCurFrame()>=10)
			{

				m_VBallFly+=50;
				m_SnakeMens_Attack2_BallInfoSprite.NextFrame(0,15);
				
				if(m_SnakeMens_Attack2InfoSprite.getCurFrame()==11)
				{
					m_TestBallFly=true;
					m_iCollision=true;
				}
				
				if(m_SnakeMens_Attack2_BallInfoSprite.getCurFrame()>=13)
				{
					m_TestBallFly=false;		
					m_VBallFly=0;
				}
			}
			if(m_SnakeMens_Attack2InfoSprite.getCurFrame()>=24)
			{
				m_STT=COOLDOWN;
				m_TimeAni=0;

			}


		}
	}
}


void SnakeMens_Attack2::UpdateStatus(float _Time)
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

void SnakeMens_Attack2::ProcessCollision(MyObject *_Obj)
{

	if(getiCollision() == true )
	{
		CRECT r;
		r.Left =m_SnakeMens_Attack2_BallInfoSprite.getX();
		r.Top = m_SnakeMens_Attack2_BallInfoSprite.getY() ;
		r.Right = r.Left+ 250;
		r.Bottom = r.Top  + 103;
		CRECT r1;
		r1.Left =m_SnakeMens_Attack2InfoSprite.getX(); ;
		r1.Top = m_SnakeMens_Attack2InfoSprite.getY() ;
		r1.Right = r1.Left+523;
		r1.Bottom = r1.Top  + 385 ;
		if(r.iCollision(_Obj->getRect())== true||r1.iCollision(_Obj->getRect())== true)
		{
			
			if(_Obj->getActive() == false  )
			{
				return ;
			}//true la chua trung

			EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
			ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
			EffectFrenzy* m_EffectFrenzy = new EffectFrenzy(_Obj->getX(), _Obj->getY());
			ManagerObject::Instance()->getListEffect()->push_back(m_EffectFrenzy);
			if (m_Direct<0)
			{

				m_iCollision=false;
				m_TestBallFly=false;
				SnakeMens_Effect2 *m_SnakeMensEffect2 = new SnakeMens_Effect2(_Obj->getX()+20,_Obj->getY()+50);
				m_SnakeMensEffect2->m_InfoSprite.setScaleX(1);
				m_SnakeMensEffect2->m_InfoSprite.setXY(_Obj->getX()-50,_Obj->getY()-150);
				ManagerObject::Instance()->getListEffect()->push_back(m_SnakeMensEffect2);
			}
			else
			{
				m_iCollision=false;
				m_TestBallFly=false;
				SnakeMens_Effect2 *m_SnakeMensEffect2 = new SnakeMens_Effect2(_Obj->getX()+20,_Obj->getY()+50);
				m_SnakeMensEffect2->m_InfoSprite.setScaleX(1);
				m_SnakeMensEffect2->m_InfoSprite.setXY(_Obj->getX()-50,_Obj->getY()-150);
				ManagerObject::Instance()->getListEffect()->push_back(m_SnakeMensEffect2);
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


void SnakeMens_Attack2::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void SnakeMens_Attack2::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_SnakeMens_Attack2InfoSprite.setScaleX(1);
		m_SnakeMens_Attack2_BallInfoSprite.setScaleX(1);
		m_SnakeMens_Attack2_BallInfoSprite.setXY(m_SnakeMens_Attack2InfoSprite.getX()-m_VBallFly,m_SnakeMens_Attack2InfoSprite.getY()+220);
		m_SnakeMens_Attack2InfoSprite.setXY(m_X+170,m_Y-55);

	}else{
		m_SnakeMens_Attack2InfoSprite.setScaleX(-1);
		m_SnakeMens_Attack2_BallInfoSprite.setScaleX(-1);
		m_SnakeMens_Attack2_BallInfoSprite.setXY(m_SnakeMens_Attack2InfoSprite.getX()+100+m_VBallFly,m_SnakeMens_Attack2InfoSprite.getY()+220);
		m_SnakeMens_Attack2InfoSprite.setXY(m_X-170,m_Y-55);

	}



	if(m_STT==ACTIVE)
	{
		m_SnakeMens_Attack2Sprite->Draw(_mtWorld,m_SnakeMens_Attack2InfoSprite,_Handler);
		if(m_TestBallFly==true)
		{
			m_SnakeMens_Attack2_BallSprite->Draw(_mtWorld,m_SnakeMens_Attack2_BallInfoSprite,_Handler);

		}

	}
}
