#include "GodLike_Teleport.h"
#include "RSMainGame.h"
#include "Global.h"
#include "InfoSprite.h"


GodLike_Teleport::GodLike_Teleport(GodLike_Beast *_GodLike)
{
	m_GodLike = _GodLike ;
	Init() ;
}

GodLike_Teleport::~GodLike_Teleport(void)
{
}

void GodLike_Teleport ::Init()
{
	m_Teleport = RSMainGame ::get()->getTeleport() ;
	m_Teleport1 = RSMainGame ::get()->getTeleport1() ;

	m_iCollision = false ;
	m_InfoSprite.setSize(568,574) ;
	m_InfoSprite1.setSize(568,574) ;
	m_STT = READY ;
	g_STT = READY ;
	
}

void GodLike_Teleport ::Active(float _X,float _Y,int _Dir)
{
	if(m_STT ==READY ) //dang ready moi cho active 
	{
		if(_Dir >0 )
		{
			m_X = _X ;
			m_Y = _Y ;
			m_Direct = _Dir ;
		}
		if(_Dir < 0)
		{
			m_X = _X ;
			m_Y = _Y ;
			m_Direct =_Dir ;
		}

		m_TimeAni = 0;
		m_iCollision = false ;
		m_InfoSprite.setCurFrame(0);
		m_STT = ACTIVE ;
		g_STT = READY ;
	}
}
void GodLike_Teleport::Animation(float _Time)
{
	if(m_STT == ACTIVE)
	{
		m_TimeAni +=_Time ;
		if(m_TimeAni >= 0.12f)
		{
			m_TimeAni -=0.12f;
			if(g_STT ==READY)
			m_InfoSprite.NextFrame(0,12) ;
			if(m_InfoSprite.getCurFrame() >=11 )
			{
				g_STT = ACTIVE ;
				if(g_STT == ACTIVE)
				{
					m_InfoSprite1.NextFrame(0,12);
					if(m_InfoSprite1.getCurFrame() >=11 )
					{
						m_STT = COOLDOWN ;
						m_TimeAni = 0;
					}
				}
			}
		}
	}
}
void GodLike_Teleport::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	UpdateStatus(_Time);
}

void GodLike_Teleport ::UpdateStatus(float _Time)
{
	switch (m_STT)
	{
	case COOLDOWN:
		m_TimeUpdate += _Time;
		if(m_TimeUpdate > 20)
		{
			m_STT = READY;
			m_TimeUpdate = 0;
		}
		break;
	}
}

void GodLike_Teleport ::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if (m_Direct<0){
		m_InfoSprite.setScaleX(1);
	    m_InfoSprite1.setScaleX(1);

		m_X = m_GodLike->getX() - 800 ;
		m_Y = m_GodLike->getY() ;

		m_InfoSprite.setXY(m_X,m_Y);
		m_InfoSprite1.setXY(m_X,m_Y) ;
	}else{
		m_X = m_GodLike->getX() + 800 ;
		m_Y = m_GodLike->getY() ;

		m_InfoSprite.setScaleX(-1);
		m_InfoSprite1.setScaleX(-1);

		m_InfoSprite.setXY(m_X,m_Y);
		m_InfoSprite1.setXY(m_X,m_Y) ;
	}

	
	if(g_STT ==READY)
	{

          	m_Teleport->Draw(_MWorld,m_InfoSprite,_Handler);
	}
	else if(g_STT ==ACTIVE)
	{
		m_Teleport1->Draw(_MWorld,m_InfoSprite1,_Handler);
	}
	
}
void GodLike_Teleport ::Release()
{

}