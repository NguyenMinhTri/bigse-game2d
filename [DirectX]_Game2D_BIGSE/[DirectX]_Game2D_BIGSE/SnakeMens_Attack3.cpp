#include "SnakeMens_Attack3.h"
#include "EffectSystem.h"
#include "ManagerObject.h"
#include "SnakeMens_Effect3.h"
#include "EffectFont.h"
#include "EffectFrenzy.h"

SnakeMens_Attack3::SnakeMens_Attack3(SnakeMans* _SnakeMens)
{
	m_SnakeMens=_SnakeMens;
	Init();
}


SnakeMens_Attack3::~SnakeMens_Attack3(void)
{
}

void SnakeMens_Attack3::Init()
{

	m_TestBallFly=false;
	m_VBallFly=100;
	m_iCollision=false;
	m_Damage = 5000;
	m_CountBall=5;
	m_STT = READY;
	setSize(212,251);
	m_SnakeMens_Attack3Sprite = RSMainGame::get()->getSnakeMans_Attack3();
	m_SnakeMens_Attack3InfoSprite.setSize(456,371);
	m_SnakeMens_Attack3InfoSprite.setDepth(0.3f);
	m_ListSnakeMens_Attack3_BallInfoSprite=new std::vector<InfoSprite>();
	m_ListSnakeMens_Attack3_BallSprite=new std::vector<Sprite*>();
	for(int i=0;i<m_CountBall;i++)
	{
		Sprite *Temp=RSMainGame::get()->getSnakeMans_Attack3_Ball();
		m_ListSnakeMens_Attack3_BallSprite->push_back(Temp);
		InfoSprite TempIF;
		TempIF.setSize(237,465);
		TempIF.setDepth(0.3f);
		m_ListSnakeMens_Attack3_BallInfoSprite->push_back(TempIF);
	}
}
void SnakeMens_Attack3::Active(float _X,float _Y,int _Dir)
{
	for(int i=0;i<4;i++)
	{
		if(m_SnakeMens->m_skillManager->getSkill(i)->getSTT()==ACTIVE)
			return;
	}
	if (m_STT == READY&&m_SnakeMens->getVY()==0) //chua tung skill
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

		m_SnakeMens_Attack3InfoSprite.setCurFrame(0);
		for (std::vector<InfoSprite>::iterator i = m_ListSnakeMens_Attack3_BallInfoSprite->begin();i<m_ListSnakeMens_Attack3_BallInfoSprite->end();i++)
		{
			(*i).setCurFrame(0);
		}
		m_TimeAni = 0;
		m_iCollision = false;
	}
}
void SnakeMens_Attack3::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_SnakeMens_Attack3InfoSprite.NextFrame(0,24);			
			if(m_SnakeMens_Attack3InfoSprite.getCurFrame()>=1)
			{
				
				m_TestBallFly=true;
				for (std::vector<InfoSprite>::iterator i = m_ListSnakeMens_Attack3_BallInfoSprite->begin();i<m_ListSnakeMens_Attack3_BallInfoSprite->end();i++)
				{
					(*i).NextFrame(0,24);
					if((*i).getCurFrame()>=23)
					{
						m_TestBallFly=false;
					}
					if((*i).getCurFrame()==18)
					{
						m_iCollision=true;
					}
				}
			}
			if(m_SnakeMens_Attack3InfoSprite.getCurFrame()>=23)
			{
				m_STT=COOLDOWN;
				m_TimeAni=0;
			}


		}
	}
}

void SnakeMens_Attack3::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 3)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}


}

void SnakeMens_Attack3::ProcessCollision(MyObject *_Obj)
{
	CRECT r1;
	r1.Left =m_SnakeMens_Attack3InfoSprite.getX(); ;
	r1.Top = m_SnakeMens_Attack3InfoSprite.getY() ;
	r1.Right = r1.Left+456;
	r1.Bottom = r1.Top  + 271 ;
	if(getiCollision() == true )//&&(/* r.iCollision(_Obj->getRect())== true ||*/r1.iCollision(_Obj->getRect())== true ))
	{
		for(int i=0;i<m_CountBall;i++)
		{
			InfoSprite temIf;
			temIf=m_ListSnakeMens_Attack3_BallInfoSprite->at(i);
			CRECT TemR;
			TemR.Left =temIf.getX();
			TemR.Top = temIf.getY() ;
			TemR.Right = TemR.Left+ 237;
			TemR.Bottom = TemR.Top  + 465;
			if(TemR.iCollision(_Obj->getRect())== true )
			{
 				if(_Obj->getActive() == false  )
 				{
 					return ;
 				}//true la chua trung
 				EffectFont* m_EffectFont = new EffectFont(_Obj->getX(), _Obj->getY(),m_Damage);
 				ManagerObject::Instance()->getListEffect()->push_back(m_EffectFont);
// 				EffectFrenzy* m_EffectFrenzy = new EffectFrenzy(_Obj->getX(), _Obj->getY());
// 				ManagerObject::Instance()->getListEffect()->push_back(m_EffectFrenzy);
				if (m_Direct<0)
				{

					m_iCollision=false;
					m_TestBallFly=false;
					SnakeMens_Effect3 *m_SnakeMensEffect3 = new SnakeMens_Effect3(_Obj->getX()+20,_Obj->getY()+50);
					m_SnakeMensEffect3->m_InfoSprite.setScaleX(1);
					m_SnakeMensEffect3->m_InfoSprite.setXY(_Obj->getX()-50,_Obj->getY()-150);
					ManagerObject::Instance()->getListEffect()->push_back(m_SnakeMensEffect3);
				}
				else
				{
					m_iCollision=false;
					m_TestBallFly=false;
					SnakeMens_Effect3 *m_SnakeMensEffect3 = new SnakeMens_Effect3(_Obj->getX()+20,_Obj->getY()+50);
					m_SnakeMensEffect3->m_InfoSprite.setScaleX(1);
					m_SnakeMensEffect3->m_InfoSprite.setXY(_Obj->getX()-50,_Obj->getY()-150);
					ManagerObject::Instance()->getListEffect()->push_back(m_SnakeMensEffect3);
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


void SnakeMens_Attack3::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);	
	UpdateStatus(_Time);
}

void SnakeMens_Attack3::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_SnakeMens_Attack3InfoSprite.setScaleX(1);
		int iAo=0;
		for (std::vector<InfoSprite>::iterator i = m_ListSnakeMens_Attack3_BallInfoSprite->begin();i<m_ListSnakeMens_Attack3_BallInfoSprite->end();i++)
		{
			iAo+=1;
			(*i).setScaleX(1);
			(*i).setXY(m_X-iAo*100+200,m_Y-80);
		}
		m_SnakeMens_Attack3InfoSprite.setXY(m_X,m_Y-90);

	}else{
		m_SnakeMens_Attack3InfoSprite.setScaleX(-1);
		int iAo=0;
		for (std::vector<InfoSprite>::iterator i = m_ListSnakeMens_Attack3_BallInfoSprite->begin();i<m_ListSnakeMens_Attack3_BallInfoSprite->end();i++)
		{
			iAo+=1;
			(*i).setScaleX(-1);
			(*i).setXY(m_X+iAo*100,m_Y-80);
		}
		m_SnakeMens_Attack3InfoSprite.setXY(m_X-90,m_Y-90);

	}
	if(m_STT==ACTIVE)
	{
		m_SnakeMens_Attack3Sprite->Draw(_mtWorld,m_SnakeMens_Attack3InfoSprite,_Handler);
		if(m_TestBallFly==true)
		{
			for(int i=0;i<m_ListSnakeMens_Attack3_BallSprite->size();i++)
			{
				Sprite *tem;
				InfoSprite temIf;
				temIf=m_ListSnakeMens_Attack3_BallInfoSprite->at(i);
				tem=m_ListSnakeMens_Attack3_BallSprite->at(i);
				tem->Draw(_mtWorld,temIf,_Handler);
			}
		}

	}
}
