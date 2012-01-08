#include "SnakeMens_Attack4.h"
#include "EffectSystem.h"
 #include "ManagerObject.h"
 #include "SnakeMens_Effect2.h"
#include "EffectFont.h"
#include "EffectFrenzy.h"
SnakeMens_Attack4::SnakeMens_Attack4(SnakeMans* _SnakeMens)
{
	m_SnakeMens=_SnakeMens;
	Init();
}


SnakeMens_Attack4::~SnakeMens_Attack4(void)
{
}

void SnakeMens_Attack4::Init()
{

	m_TestBallFly=false;
	m_iCollision=false;
	m_Damage = 2000;

	m_STT = READY;
	setSize(415,100);
	m_SnakeMens_Attack4Sprite = RSMainGame::get()->getSnakeMans_Attack4();
	m_SnakeMens_Attack4_BallSprite = RSMainGame::get()->getSnakeMans_Attack4_Ball();

	m_SnakeMens_Attack4_BallInfoSprite.setDepth(0.3f);
	m_SnakeMens_Attack4_BallInfoSprite.setSize(622,563);
	m_SnakeMens_Attack4InfoSprite.setSize(328,522);
	m_SnakeMens_Attack4InfoSprite.setDepth(0.3f);
}
void SnakeMens_Attack4::Active(float _X,float _Y,int _Dir)
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

		m_SnakeMens_Attack4InfoSprite.setCurFrame(0);
		m_SnakeMens_Attack4_BallInfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
		m_TestBallFly=false;
	}
}
void SnakeMens_Attack4::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_SnakeMens_Attack4InfoSprite.NextFrame(0,24);			
			if(m_SnakeMens_Attack4InfoSprite.getCurFrame()>=5)
			{
				m_SnakeMens_Attack4_BallInfoSprite.NextFrame(0,19);

				if(m_SnakeMens_Attack4InfoSprite.getCurFrame()==11)
				{
					m_TestBallFly=true;
					m_iCollision=true;
				}

				if(m_SnakeMens_Attack4_BallInfoSprite.getCurFrame()>=18)
				{
					m_TestBallFly=false;		
					m_VBallFly=0;
				}
			}
			if(m_SnakeMens_Attack4InfoSprite.getCurFrame()>=23)
			{
				m_STT=COOLDOWN;
				m_TimeAni=0;

			}

		}
	}
}


void SnakeMens_Attack4::UpdateStatus(float _Time)
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

void SnakeMens_Attack4::ProcessCollision(MyObject *_Obj)
{

	if(getiCollision() == true )
	{
		CRECT r;
		r.Left =m_SnakeMens_Attack4_BallInfoSprite.getX();
		r.Top = m_SnakeMens_Attack4_BallInfoSprite.getY() ;
		r.Right = r.Left+ 622;
		r.Bottom = r.Top  + 622;
		CRECT r1;
		r1.Left =m_SnakeMens_Attack4InfoSprite.getX(); ;
		r1.Top = m_SnakeMens_Attack4InfoSprite.getY() ;
		r1.Right = r1.Left+328;
		r1.Bottom = r1.Top  + 522 ;
		if(r.iCollision(_Obj->getRect())== true||r1.iCollision(_Obj->getRect())== true)
		{

			if(_Obj->getActive() == false  )
			{
				return ;
			}//true la chua trung

			EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
			ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
// 			EffectFrenzy* m_EffectFrenzy = new EffectFrenzy(_Obj->getX(), _Obj->getY());
// 			ManagerObject::Instance()->getListEffect()->push_back(m_EffectFrenzy);
// 			if (m_Direct<0)
// 			{
// 
// 				m_iCollision=false;
// 				for(int i=0;i<5;i++)
// 				{
// 					SnakeMens_Effect2 *m_SnakeMensEffect2 = new SnakeMens_Effect2(_Obj->getX()+20,_Obj->getY()+40);
// 					m_SnakeMensEffect2->m_InfoSprite.setScaleX(1);
// 					m_SnakeMensEffect2->m_InfoSprite.setXY(_Obj->getX()-50*(2-i),_Obj->getY()-150);
// 					ManagerObject::Instance()->getListEffect()->push_back(m_SnakeMensEffect2);
// 				}
// 				
// 			}
// 			else
// 			{
// 
// 				m_iCollision=false;
// 				for(int i=0;i<5;i++)
// 				{
// 				SnakeMens_Effect2 *m_SnakeMensEffect2 = new SnakeMens_Effect2(_Obj->getX()+20,_Obj->getY()+40);
// 				m_SnakeMensEffect2->m_InfoSprite.setScaleX(1);
// 				m_SnakeMensEffect2->m_InfoSprite.setXY(_Obj->getX()-50*(2-i),_Obj->getY()-150);
// 				ManagerObject::Instance()->getListEffect()->push_back(m_SnakeMensEffect2);
// 				}
// 			}

			_Obj->setActive(false);
/*			_Obj->setFrenzey(true);*/
			_Obj->setHp(_Obj->getHp() - getDamage());
			if(_Obj->getHp() <= 0)
			{
				_Obj->setLife(false); 
			}	
		}

	}
}


void SnakeMens_Attack4::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void SnakeMens_Attack4::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_SnakeMens_Attack4InfoSprite.setScaleX(1);
		m_SnakeMens_Attack4_BallInfoSprite.setScaleX(1);
		m_SnakeMens_Attack4InfoSprite.setXY(m_X+270,m_Y-250);
		m_SnakeMens_Attack4_BallInfoSprite.setXY(m_SnakeMens_Attack4InfoSprite.getX()-100,m_SnakeMens_Attack4InfoSprite.getY()+30);
		

	}else{
		m_SnakeMens_Attack4InfoSprite.setScaleX(-1);
		m_SnakeMens_Attack4_BallInfoSprite.setScaleX(-1);
		m_SnakeMens_Attack4InfoSprite.setXY(m_X-50,m_Y-250);
		m_SnakeMens_Attack4_BallInfoSprite.setXY(m_SnakeMens_Attack4InfoSprite.getX()-100,m_SnakeMens_Attack4InfoSprite.getY()+30);
	

	}



	if(m_STT==ACTIVE)
	{
 		m_SnakeMens_Attack4Sprite->Draw(_mtWorld,m_SnakeMens_Attack4InfoSprite,_Handler);
		if(m_TestBallFly==true)
		{
			m_SnakeMens_Attack4_BallSprite->Draw(_mtWorld,m_SnakeMens_Attack4_BallInfoSprite,_Handler);

		}

	}
}
