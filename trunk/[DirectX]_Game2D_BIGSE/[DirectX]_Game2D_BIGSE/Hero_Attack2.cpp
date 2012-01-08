#include "Hero_Attack2.h"
#include "EffectSystem.h"
#include "ManagerObject.h"
#include "Hero_Effect1.h"
#include "EffectFont.h"
#include "SoundGame.h"

Hero_Attack2::Hero_Attack2(Hero* _Hero)
{
	m_Hero=_Hero;
	Init();
}


Hero_Attack2::~Hero_Attack2(void)
{
}

void Hero_Attack2::Init()
{
	m_iCollision=false;
	m_Damage = 400;

	m_STT = READY;
	setSize(294,120);
	m_Hero_Attack2Sprite = RSMainGame::get()->getHero_Attack2();
	m_Hero_Attack2InfoSprite.setSize(294,164);
	m_Hero_Attack2InfoSprite.setDepth(0.3f);

}
void Hero_Attack2::Active(float _X,float _Y,int _Dir)
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

		m_Hero_Attack2InfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
	}
}
void Hero_Attack2::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		SoundGame ::Instance()->PlaySolarFlare();
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_Hero_Attack2InfoSprite.NextFrame(0,14);			
			if(m_Hero_Attack2InfoSprite.getCurFrame()>=7)
			{
				m_iCollision=true;
			}
			if(m_Hero_Attack2InfoSprite.getCurFrame()>=13)
			{
// 				if (m_Direct<0)
// 				{
// 					m_Hero->setXY(m_Hero->getX()-160,m_Hero->getY());
// 				}
// 				else
// 				{
// 					m_Hero->setXY(m_Hero->getX()+160,m_Hero->getY());
// 				}
				m_STT=COOLDOWN;
				m_TimeAni=0;
			}


		}
	}
}


void Hero_Attack2::UpdateStatus(float _Time)
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

void Hero_Attack2::ProcessCollision(MyObject *_Obj)
{
	CRECT r1;
	r1.Left =m_Hero_Attack2InfoSprite.getX(); ;
	r1.Top = m_Hero_Attack2InfoSprite.getY() ;
	r1.Right = r1.Left+ 294;
	r1.Bottom = r1.Top  + 164 ;
	if(getiCollision() == true &&r1.iCollision(_Obj->getRect())== true )
	{

		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung
		EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
			if (m_Direct<0)
			{
				Hero_Effect1 *m_HeroEffect1 = new Hero_Effect1(_Obj->getX(),_Obj->getY()+50);
				m_HeroEffect1->m_InfoSprite.setScaleX(1);
				m_HeroEffect1->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2-25,r1.Top);
				ManagerObject::Instance()->getListEffect()->push_back(m_HeroEffect1);
			}
			else
			{
				Hero_Effect1 *m_HeroEffect1 = new Hero_Effect1(_Obj->getX()+150,_Obj->getY()+50);
				m_HeroEffect1->m_InfoSprite.setScaleX(-1);
				m_HeroEffect1->m_InfoSprite.setXY(_Obj->getX()+_Obj->getWidth()/2+25,r1.Top);
				ManagerObject::Instance()->getListEffect()->push_back(m_HeroEffect1);
			}

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - getDamage());
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}


void Hero_Attack2::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void Hero_Attack2::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_Hero_Attack2InfoSprite.setScaleX(1);
		m_Hero_Attack2InfoSprite.setXY(m_X+75,m_Y-20);

	}else{
		m_Hero_Attack2InfoSprite.setScaleX(-1);
		m_Hero_Attack2InfoSprite.setXY(m_X-45,m_Y-20);

	}



	if(m_STT==ACTIVE)
	{
		m_Hero_Attack2Sprite->Draw(_mtWorld,m_Hero_Attack2InfoSprite,_Handler);

	}
}

