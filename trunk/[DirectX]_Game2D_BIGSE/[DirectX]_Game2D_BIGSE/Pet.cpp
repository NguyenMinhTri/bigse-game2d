#include "Pet.h"
#include "MyObject.h"
#include "RSMainGame.h"
#include "Global.h"

Pet ::Pet(MyObject*  _Character)
{
	Init();
	m_Character =  _Character ;
}

Pet::~Pet(void)
{
}

void Pet :: Init()
{
	m_TimeLife = 50;
	m_TimeCoolDown = 5;
	m_Partner = RSMainGame::get()->getPartner();
	m_InfoSprite.setSize(100,80);
	setSize(62,62);
	m_STT = READY;
    p_stt = P_READY;
	m_iCollision = false ;
}

void Pet ::Active(float _X,float _Y,int _Dir)
{
	if (m_STT == READY) 
	{
		if (_Dir>0)
		{
			m_X = _X -70;
			m_Y = _Y ;
			m_Direct = _Dir;
		} 
		else
		{
			m_X = _X +30;
			m_Y = _Y ;	
			m_Direct = _Dir;
		}
		m_STT = ACTIVE;
		m_InfoSprite.setCurFrame(0);
		m_TimeAni = 0;
		m_iCollision = false ;
	}
}

void Pet ::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight )
{
	float NextX,NextY;
	m_Direct = m_Character->getDirection();
#pragma region RIGHT
	if (m_Direct > 0){
		NextX =m_Character->getX() + 70 + _Time* m_Vx; //thoi gian thuc
		if (NextX >= _MaxWidth - m_Width)
		{
			NextX = _MaxWidth - m_Width;
		}

		bool iColTer = false;
		for (int i = (m_X + m_Width)/g_CELL ; i <  (NextX+m_Width)/g_CELL;i++)
		{
			for (int j = m_Y/g_CELL;j < (int)((m_Y+m_Height-1)/g_CELL) +1;j++ ){
				if (_Terrain[i][j]!=0){
					iColTer = true;
					m_X = g_CELL * (i) - m_Width;
					break;
				}
			}
			if (iColTer == true){
				break;
			}
		}

		if (iColTer == false){
			m_X = NextX;
		}

#pragma endregion RIGHT

#pragma region LEFT
	}else{
		if (m_Direct<0){

			NextX= m_Character->getX() - 130 + _Time* m_Vx;
			if (NextX <= 0)
			{
				NextX = 0;
			}
			bool iColTer = false;
			for (int i = m_X/g_CELL-1; i >  NextX/g_CELL-1;i--) // 
			{
				for (int j = m_Y/g_CELL ;j < int((m_Y+m_Height-1)/g_CELL) +1 ; j++ )
				{
					if (_Terrain[i][j]!=0){
						iColTer = true;
						m_X = g_CELL * (i+1);
						break;
					}
				} 
				if (iColTer == true)
				{
					break;
				}
			}

			if (iColTer == false)
			{
				m_X = NextX;
			}
		}		
	}
#pragma endregion LEFT

	if (m_Vy==0)
	{
		m_Direct = 0;
	}
#pragma region DOWN
	m_Vy+= _Time*m_Gravity;
	NextY = m_Character->getY() + m_Vy*_Time + 0.5*(_Time*_Time)*m_Gravity;
	if (NextY >= (_MaxHeight - m_Height))
	{
		NextY =  _MaxHeight - m_Height;
	}
	if (NextY <= 0)
	{
		NextY = 0;
		m_Vy = fabs(m_Vy);
	}

	if (m_Vy >= 0){

		bool iColTer = false;
		for (int j = (m_Y+m_Height)/g_CELL; j <  (NextY+m_Height)/g_CELL ;j++){
			for (int i = m_X/g_CELL;i < (m_X+m_Width)/g_CELL;i++ ){
				if (_Terrain[i][j]!=0){
					iColTer = true;
					m_Y = g_CELL * (j) - m_Height;
					m_Vy = 0;
					break;
				}
			}
			if (iColTer == true){
				break;
			}

		}
		if (iColTer == false){
			m_Y = NextY;
		}
#pragma endregion DOWN

#pragma region UP
	}else{
		NextY = m_Character->getY() + m_Vy* _Time;
		int n = (NextY/g_CELL);
		int m = (m_Y/g_CELL);
		if (n!=m ){

			bool iColTer = false;
			for (int j = m_Y/g_CELL-1; j >  NextY/g_CELL-1;j--){
				for (int i = m_X/g_CELL;i < (m_X+m_Width)/g_CELL;i++ ){
					if (_Terrain[i][j]!=0){
						iColTer = true;
						m_Y = g_CELL * (j+1);
						m_Vy = fabs(m_Vy);
						break;
					}
				}
				if (iColTer == true){
					break;
				}
			}

			if (iColTer == false){
				m_Y = NextY;
			}

		}else{
			m_Y = NextY;
		}
	}
#pragma endregion UP
}

void Pet :: Animation(float _Time)
{
	if (m_STT == ACTIVE)
	{
		m_TimeAni+= _Time;
		if (m_TimeAni>=0.12f)
		{
			m_TimeAni-= 0.12f;
			if(m_iCollision == true)
			{
				m_InfoSprite.NextFrame(6,6);
				if(m_InfoSprite.getCurFrame() ==11 )
				{
					m_InfoSprite.setCurFrame(6);
					p_stt = P_READY;
					m_TimeAni =0;
				}
			}
			else{
				m_InfoSprite.NextFrame(0,6);
				if (m_InfoSprite.getCurFrame() ==5)
				{			
					m_InfoSprite.setCurFrame(0);
					m_TimeAni =0;
				}
			}
		}
	}
}
void Pet ::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case ACTIVE :
		m_TimeUpdate+= _Time;
		if(m_TimeUpdate > m_TimeLife)
		{
			m_STT = COOLDOWN ;
			m_TimeUpdate = 0;
		}
		break;
	case COOLDOWN:
		m_TimeUpdate +=_Time;
		if(m_TimeUpdate > m_TimeCoolDown)
		{
			m_STT = READY ;
			m_TimeUpdate = 0;
		}
		break; 
	}
}

void Pet :: ProcessCollision(MyObject* _Obj)
{
	if(getRect().iCollision(_Obj->getRect())== true )
	{
		m_iCollision = true ;
		p_stt = P_COLLISION ;
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
	else if(getRect().iCollision(_Obj->getRect())== false  && p_stt == P_READY)
	{
		m_iCollision = false ;
	}
}

void Pet ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Move(_Time, _Terrain, _MaxWidth,_MaxHeight);
	Animation(_Time);
	UpdateStatus(_Time);
}

void Pet :: Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	m_Direct = m_Character->getDirection();
	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	}else{
		m_InfoSprite.setScaleX(-1);
	}
	m_InfoSprite.setXY(m_X,m_Y);
	m_Partner->Draw(_MWorld,m_InfoSprite,_Handler);
}