#include "SnakeMens_Attack1.h"
#include "EffectSystem.h"
#include "ManagerObject.h"
#include "SnakeMens_Effect1.h"
#include "EffectFont.h"
SnakeMens_Attack1::SnakeMens_Attack1(SnakeMans* _SnakeMens)
{
	m_SnakeMens=_SnakeMens;
	Init();
}


SnakeMens_Attack1::~SnakeMens_Attack1(void)
{
}

void SnakeMens_Attack1::Init()
{
	m_iCollision=false;
	m_Damage = 2000;

	m_STT = READY;
	setSize(721,280);
	m_SnakeMens_Attack1Sprite = RSMainGame::get()->getSnakeMans_attack1();
	m_SnakeMens_Attack1InfoSprite.setSize(721,280);
	m_SnakeMens_Attack1InfoSprite.setDepth(0.3f);

}
void SnakeMens_Attack1::Active(float _X,float _Y,int _Dir)
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

		m_SnakeMens_Attack1InfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false;
	}
}
void SnakeMens_Attack1::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_SnakeMens_Attack1InfoSprite.NextFrame(0,24);			
			if(m_SnakeMens_Attack1InfoSprite.getCurFrame()>=10)
			{
				m_iCollision=true;
			}
			if(m_SnakeMens_Attack1InfoSprite.getCurFrame()>=23)
			{
				m_STT=COOLDOWN;
				m_TimeAni=0;
			}


		}
	}
}


void SnakeMens_Attack1::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 0.5f)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}


}

void SnakeMens_Attack1::ProcessCollision(MyObject *_Obj)
{
	CRECT r1;
	r1.Left =m_SnakeMens_Attack1InfoSprite.getX(); ;
	r1.Top = m_SnakeMens_Attack1InfoSprite.getY() ;
	r1.Right = r1.Left+ 721;
	r1.Bottom = r1.Top  + 280 ;
	if(getiCollision() == true &&r1.iCollision(_Obj->getRect())== true )
	{

		if(_Obj->getActive() == false  )
		{
			return ;
		}//true la chua trung
		EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY()+_Obj->getHeight()/2,m_Damage);
		ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
		if (m_Direct<0)
		{
			SnakeMens_Effect1 *m_SnakeEffect1 = new SnakeMens_Effect1(_Obj->getX(),_Obj->getY()+50);
			m_SnakeEffect1->m_InfoSprite.setScaleX(1);
			m_SnakeEffect1->m_InfoSprite.setXY(_Obj->getX()-50,_Obj->getY()-100);
			ManagerObject::Instance()->getListEffect()->push_back(m_SnakeEffect1);
		}
		else
		{
			SnakeMens_Effect1 *m_SnakeEffect1 = new SnakeMens_Effect1(_Obj->getX()+150,_Obj->getY()+50);
			m_SnakeEffect1->m_InfoSprite.setScaleX(-1);
						m_SnakeEffect1->m_InfoSprite.setXY(_Obj->getX()+150,_Obj->getY()-100);
			ManagerObject::Instance()->getListEffect()->push_back(m_SnakeEffect1);
		}

		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - getDamage());
		if(_Obj->getHp() <= 0)
		{
			_Obj->setLife(false); 
		}	
	}
}


void SnakeMens_Attack1::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void SnakeMens_Attack1::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_SnakeMens_Attack1InfoSprite.setScaleX(1);
		m_SnakeMens_Attack1InfoSprite.setXY(m_X+190,m_Y);

	}else{
		m_SnakeMens_Attack1InfoSprite.setScaleX(-1);
		m_SnakeMens_Attack1InfoSprite.setXY(m_X-30,m_Y);

	}



	if(m_STT==ACTIVE)
	{
		m_SnakeMens_Attack1Sprite->Draw(_mtWorld,m_SnakeMens_Attack1InfoSprite,_Handler);

	}
}

