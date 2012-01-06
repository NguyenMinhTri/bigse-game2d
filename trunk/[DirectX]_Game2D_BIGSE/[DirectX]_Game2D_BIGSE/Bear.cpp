#include "Bear.h"
#include "ManagerObject.h"
#include "BearAttack.h"
#include "EffectDieBear.h"
Bear::Bear(void)
{
	Init();
}


Bear::~Bear(void)
{
	
}
void Bear ::Init()
{
	v_x = g_GodLike_Beast ;
	setFrenzey(false);
	m_Direct = 1;
	m_STT = ACTIVE;
	m_BearMove= RSMainGame::get()->getBearMove() ;
	m_InfoMove.setSize(78,87);
	m_InfoMove.setDepth(0.2);
	m_HP = 2100 ;
	setSize(78,87);
	m_Hit = false;
	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new BearAttack(this));
}
void Bear ::Animation(float _Time)
{	
	m_TimeAni += _Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.16f)
		{
			m_TimeAni -= 0.16f;
			if (m_Vy != 0)
			{
				m_InfoMove.setCurFrame(1);
			}
			else
			{
				m_InfoMove.NextFrame(0,5);
			}
		}
		break;
	}
}
void Bear ::UpdateStatus(float _Time)
{
	if(!m_iActive )
	{
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 1 )
		{
			m_iActive = true ;
			m_TimeUpdate =0;
		}
	}
	if(getFrenzy() == true)
	{
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 1.95)
		{
			setFrenzey(false);
			m_TimeUpdate =0;
		}
	}
}
void Bear ::ProcessCollision(MyObject* _Obj)
{
	m_skillManager->ProcessCollision(_Obj);
	if(!getRect().iCollision(_Obj->getRect()))
	{
		if(abs(_Obj->getX() - m_X ) < 500 ) 
		{
			if(_Obj->getX() > m_X )
			{
				m_Direct =1 ;
			}
			if(_Obj->getX() < m_X)
			{
				m_Direct = -1 ;
			}
		}
	}
	if(abs(_Obj->getX() - m_X ) < 250) 
	{
		ActiveSkill(0);		
	}
}
void Bear::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	if(getLife() == false)
	{
		int random ;
		random = rand() % 4 ;
		switch(random)
		{
		case  0 :
			Item *_item = new Item(m_X,m_Y);
			ManagerObject::Instance()->getListItem()->push_back(_item);
			break ;

		}
		EffectDieBear *_EffectDie = new EffectDieBear(this,m_X,m_Y);
		ManagerObject ::Instance()->getListEffect()->push_back(_EffectDie);
	}
	if(m_skillManager->getSkill(0)->getSTT()==ACTIVE)
	{
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
	}
	else if(m_skillManager->getSkill(0)->getSTT() !=ACTIVE)
	{
		if(getFrenzy() ==false)
		{
			Move(_Time,_Terrain,_MaxWidth,_MaxHeight);	
		}
		Animation(_Time);
		UpdateStatus(_Time);
		m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight); //??
	}
}
void Bear::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if (m_skillManager->getSkill(0)->getSTT()==ACTIVE)
	{
		m_skillManager->getSkill(0)->Draw(_MWorld,_Handler) ;
	}
	if (m_Direct<0){
		m_InfoMove.setScaleX(1);
	}else{
		m_InfoMove.setScaleX(-1);
	}
	if (m_skillManager->getSkill(0)->getSTT()!=ACTIVE)
	{
		m_InfoMove.setXY(m_X,m_Y);
		m_BearMove->Draw(_MWorld,m_InfoMove,_Handler);
	}
}
void Bear ::Release()
{

}