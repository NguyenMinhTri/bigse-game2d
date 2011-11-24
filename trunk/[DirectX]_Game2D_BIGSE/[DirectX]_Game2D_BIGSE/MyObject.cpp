#include "MyObject.h"
#include "Global.h"


MyObject::MyObject(void)
{
	m_X			= 0;
	m_Y			= 0;
	m_Width		= 0;
	m_Height	= 0;
	m_Vx		= 0;
	m_Vy		= 0;
	m_TimeUpdate= 0;
	m_TimeAni	= 0;

	m_iFrenzy = false;
    m_iFire = false ;
	m_iLife = true;
	m_iActive = true;

	m_ID		= PLAYER;
	m_STT		= ACTIVE;
	m_OldSTT	= ACTIVE;
}


MyObject::~MyObject(void)
{

}
