#include "Hero_Attack4.h"
#include "EffectSystem.h"
#include "ManagerObject.h"
#include "Hero_Effect2.h"
#include "EffectFont.h"
#include "SoundGame.h"
Hero_Attack4::Hero_Attack4(Hero* _Hero)
{
	m_Hero=_Hero;
	Init();
}


Hero_Attack4::~Hero_Attack4(void)
{
}

void Hero_Attack4::Init()
{

	m_TestBallFly=false;
	m_VBallFly=100;
	m_iCollision=false;
	m_Damage = 5000;
	m_CountBall=10;
	m_STT = READY;
	setSize(212,251);
	m_Hero_Attack4Sprite = RSMainGame::get()->getHero_Attack4();
	m_Hero_Attack4InfoSprite.setSize(212,251);
	m_Hero_Attack4InfoSprite.setDepth(0.3f);
	m_ListHero_Attack4_BallInfoSprite=new std::vector<InfoSprite>();
	m_ListHero_Attack4_BallSprite=new std::vector<Sprite*>();
	for(int i=0;i<m_CountBall;i++)
	{
		Sprite *Temp=RSMainGame::get()->getHero_Attack3_Ball();
		m_ListHero_Attack4_BallSprite->push_back(Temp);
		InfoSprite TempIF;
		TempIF.setSize(97,150);
		TempIF.setDepth(0.3f);
		m_ListHero_Attack4_BallInfoSprite->push_back(TempIF);
	}
}
void Hero_Attack4::Active(float _X,float _Y,int _Dir)
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

		m_Hero_Attack4InfoSprite.setCurFrame(0);
		for (std::vector<InfoSprite>::iterator i = m_ListHero_Attack4_BallInfoSprite->begin();i<m_ListHero_Attack4_BallInfoSprite->end();i++)
		{
			(*i).setCurFrame(0);
		}
		m_TimeAni = 0;
		m_iCollision = false;
	}
}
void Hero_Attack4::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		SoundGame ::Instance()->PlayKaMeHaMe();
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_Hero_Attack4InfoSprite.NextFrame(0,18);			
 			if(m_Hero_Attack4InfoSprite.getCurFrame()>=8)
 			{
 				m_iCollision=true;
				m_TestBallFly=true;
				for (std::vector<InfoSprite>::iterator i = m_ListHero_Attack4_BallInfoSprite->begin();i<m_ListHero_Attack4_BallInfoSprite->end();i++)
				{
					(*i).NextFrame(0,6);
					if((*i).getCurFrame()>=4)
					{
						m_TestBallFly=false;
					}
				}
 			}
			if(m_Hero_Attack4InfoSprite.getCurFrame()>=17)
			{
				m_STT=COOLDOWN;
				m_TimeAni=0;
			}


		}
	}
}

void Hero_Attack4::UpdateStatus(float _Time)
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

void Hero_Attack4::ProcessCollision(MyObject *_Obj)
{
 	CRECT r1;
	r1.Left =m_Hero_Attack4InfoSprite.getX(); ;
	r1.Top = m_Hero_Attack4InfoSprite.getY() ;
	r1.Right = r1.Left+212;
	r1.Bottom = r1.Top  + 251 ;
	if(getiCollision() == true )//&&(/* r.iCollision(_Obj->getRect())== true ||*/r1.iCollision(_Obj->getRect())== true ))
	{
		for(int i=0;i<m_CountBall;i++)
		{
			InfoSprite temIf;
			temIf=m_ListHero_Attack4_BallInfoSprite->at(i);
			CRECT TemR;
			TemR.Left =temIf.getX();
			TemR.Top = temIf.getY() ;
			TemR.Right = TemR.Left+ 97;
			TemR.Bottom = TemR.Top  + 150;
			if(TemR.iCollision(_Obj->getRect())== true )
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
						m_HeroEffect2->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2-25,TemR.Top);
						ManagerObject::Instance()->getListEffect()->push_back(m_HeroEffect2);
					}
					else
					{
						Hero_Effect2 *m_HeroEffect2 = new Hero_Effect2(_Obj->getX()+130,_Obj->getY()+50);
						m_HeroEffect2->m_InfoSprite.setScaleX(-1);
						m_HeroEffect2->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2+25,TemR.Top);
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
			
	}
}


void Hero_Attack4::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void Hero_Attack4::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_Hero_Attack4InfoSprite.setScaleX(1);
		int iAo=0;
		for (std::vector<InfoSprite>::iterator i = m_ListHero_Attack4_BallInfoSprite->begin();i<m_ListHero_Attack4_BallInfoSprite->end();i++)
		{
			iAo+=1;
			(*i).setScaleX(1);
			(*i).setXY(m_X-iAo*50+200,m_Y-60);
		}
		m_Hero_Attack4InfoSprite.setXY(m_X+90,m_Y-147);

	}else{
		m_Hero_Attack4InfoSprite.setScaleX(-1);
		int iAo=0;
		for (std::vector<InfoSprite>::iterator i = m_ListHero_Attack4_BallInfoSprite->begin();i<m_ListHero_Attack4_BallInfoSprite->end();i++)
		{
			iAo+=1;
			(*i).setScaleX(-1);
			(*i).setXY(m_X+iAo*50,m_Y-60);
		}
		m_Hero_Attack4InfoSprite.setXY(m_X-60,m_Y-147);

	}
	if(m_STT==ACTIVE)
	{
		m_Hero_Attack4Sprite->Draw(_mtWorld,m_Hero_Attack4InfoSprite,_Handler);
		if(m_TestBallFly==true)
		{
			for(int i=0;i<m_ListHero_Attack4_BallSprite->size();i++)
			{
				Sprite *tem;
				InfoSprite temIf;
				temIf=m_ListHero_Attack4_BallInfoSprite->at(i);
				tem=m_ListHero_Attack4_BallSprite->at(i);
				tem->Draw(_mtWorld,temIf,_Handler);
			}
		}

	}
}
