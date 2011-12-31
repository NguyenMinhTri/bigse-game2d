#include "Hero_Attack1.h"


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
	Test1=false;
	V=100;
	m_iCollision=false;
	m_Damage = 1;

	m_STT = READY;
	setSize(415,143);
	m_Hero_Attack1Sprite = RSMainGame::get()->getHero_Attack1();
	m_Hero_Attack1_BallSprite = RSMainGame::get()->getHero_Attack1_Ball();

	m_Hero_Attack1_BallInfoSprite.setSize(415,143);
	m_Hero_Attack1InfoSprite.setSize(570,255);

}
void Hero_Attack1::Active(float _X,float _Y,int _Dir)
{
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
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_Hero_Attack1InfoSprite.NextFrame(0,15);			
			if(m_Hero_Attack1InfoSprite.getCurFrame()>=8)
			{
				m_iCollision=true;
				V+=100;
				m_Hero_Attack1_BallInfoSprite.NextFrame(0,4);
				Test1=true;
				if(m_Hero_Attack1_BallInfoSprite.getCurFrame()>=3)
				{
					Test1=false;
					V=100;

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
		if(m_TimeUpdate > 1)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}


}

void Hero_Attack1::ProcessCollision(MyObject *_Obj)
{

	if(getiCollision() == true && getRect().iCollision(_Obj->getRect())== true )
	{
		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung
		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - getDamage());
		if(_Obj->getHp() == 0)
		{
			_Obj->setLife(false); 
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
		m_Hero_Attack1_BallInfoSprite.setXY(m_X-100-V,m_Y-30);
		
	}else{
		m_Hero_Attack1InfoSprite.setScaleX(-1);
		m_Hero_Attack1_BallInfoSprite.setScaleX(-1);
		m_Hero_Attack1_BallInfoSprite.setXY(m_X+100+V,m_Y-30);
		
	}
	m_Hero_Attack1InfoSprite.setXY(m_X-150,m_Y-67);
	

	if(m_STT==ACTIVE)
	{
		m_Hero_Attack1Sprite->Draw(_mtWorld,m_Hero_Attack1InfoSprite,_Handler);
		if(Test1==true)
		{
			m_Hero_Attack1_BallSprite->Draw(_mtWorld,m_Hero_Attack1_BallInfoSprite,_Handler);

		}

	}
}
