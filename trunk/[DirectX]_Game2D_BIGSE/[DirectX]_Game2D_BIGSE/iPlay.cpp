
#include "iPlay.h"

iPlay::iPlay(LPDIRECT3DDEVICE9 Device)
{
	m_Device=Device;
}
iPlay::~iPlay(void)
{
}
void iPlay::SetCurState (iState* _curstate)
{
	m_CurState=_curstate;
}
void iPlay::SetNextState (iState* _nextstate)
{
	m_NextState=_nextstate;
}
iState* iPlay::GetCurState ()
{
	return m_CurState;
}
iState* iPlay::GetNextState ()
{
	return m_NextState;
}
void iPlay::SetDevice(LPDIRECT3DDEVICE9 Device)
{
	m_Device=Device;
}
LPDIRECT3DDEVICE9 iPlay::GetDevice()
{
	return m_Device;
}