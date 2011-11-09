#include "iState.h"

iState::iState(iPlay* GamePlay)
{
	m_iPlay = GamePlay;	
	m_Device = GamePlay->GetDevice();
}
iState::~iState(void)
{
}
void iState::SetGamePlay(iPlay* GamePlay)
{
	m_iPlay=GamePlay;
}
void iState::SetIDState(int _Id)
{
	m_ID =_Id;
}
int iState::GetIDState ()
{
	return m_ID;
}
iPlay* iState::GetGamePlay()
{
	return m_iPlay;
}