#include "CallPet.h"
#include "Global.h"
#include "RSMainGame.h"

CallPet::CallPet(void)
{
	Init();
}


CallPet::~CallPet(void)
{
}

void CallPet::Init()
{
	m_Damage = 1;
	m_Combo = 0;
	m_STT = READY;
	m_InfoSprite.setSize(283,214);
	setSize(283,189);
	m_SSkill = RSMainGame::get()->getPet();
}

void CallPet::Active (float _X,float _Y,int _Dir)
{
	if (m_STT == READY) //chua tung CallPet
	{
		if (_Dir>0)
		{
			m_X = _X  + 50;
			/*m_Y = _Y-(394-85);*/
			m_Y = _Y-(189-85);
			m_Dir = _Dir;
		} 
		else
		{
			m_X = _X -m_Width ;
			/*	m_Y = _Y-(394-85);*/
			m_Y = _Y-(189 - 85);	
			m_Dir = _Dir;
		}

		m_STT = ACTIVE;
		m_InfoSprite.setCurFrame(0);

		m_TimeAni = 0;

	}

}

bool CallPet::iCollision (MyObject* _Obj) {
	return false;
}

void CallPet::ProcessCollision(MyObject* _Obj){
	if ( m_STT!= ACTIVE ) 
	{
		return;
	}
	if(!getRect().iCollision(_Obj->getRect()))
	{
		return ;
	}
	else {
		if(_Obj->getActive() == false )
		{
			return ;
		}//true la chua trung
		_Obj->setActive(false);
		_Obj->setHp(_Obj->getHp() - getDamage()  );
		if(_Obj->getHp() == 0)
		{
			_Obj->setLife(false); 
		}		
	}
}



int CallPet::getDamageEX(int _Damage, int _Offset)
{
	return _Damage+ rand()%_Offset;
}

void CallPet::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	//       if(m_InfoSprite.getCurFrame() == 11  )
	// 	  {
	// 		  m_InfoSprite.setX(m_InfoSprite.getX() +3 );
	// 	  }
}

void CallPet::Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			m_InfoSprite.NextFrame(0,21);
			if(m_InfoSprite.getCurFrame() > 11  && m_InfoSprite.getCurFrame() <13 )
			{
				/*m_InfoSprite.setX(m_InfoSprite.getX() + 30 );*/
				if(m_Dir >0)
				{
			     	m_X +=400;
				}
				else if(m_Dir < 0)
				{
					m_X -= 400;
				}

			}

		}
	}

}

void CallPet::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case ACTIVE:
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > 2.52)
		{
			m_STT = COOLDOWN;
			m_TimeUpdate = 0;
		}
		break;
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

void CallPet::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}

void CallPet::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){

	if (m_Dir<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY(m_X,m_Y);
	m_SSkill->Draw(_MWorld,m_InfoSprite,_Handler);

}

void CallPet::Release()
{
}
