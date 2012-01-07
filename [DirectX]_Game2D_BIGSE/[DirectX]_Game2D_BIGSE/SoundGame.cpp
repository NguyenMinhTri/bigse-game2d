#include "SoundGame.h"
SoundGame* SoundGame::m_Instance = NULL;
SoundGame::SoundGame()
{
	
}
SoundGame::~SoundGame()
{

}
void SoundGame::SetSound(bool _val)
{
	SActi=BackActi=EffActi=_val;
}
void SoundGame::SetSoundBackGround(bool _val)
{
	if (_val)
	{
		SActi=_val;
		BackActi=_val;
	} 
	else
	{
		BackActi=_val;
	}
}
void SoundGame::SetSoundEffect(bool _val)
{
	if (_val)
	{
		SActi=_val;
		EffActi=_val;
	} 
	else
	{
		EffActi=_val;
	}
}
void SoundGame::Init(HWND _hwnd)
{
	phwnd= _hwnd;
	SDev = new DSound;
	SDev->Init(phwnd);

	SBackGame= SDev->LoadSound("data\\sound\\sback.wav");
}

void SoundGame::PlayBackGame()
{
	SBackGame->Stop();
	if (BackActi)
	{
		SBackGame->Play(0,DSBPLAY_LOOPING);
	}
}
void SoundGame::PlayEffect()
{
	if (EffActi)
	{
		//SPerffect->Play();
	}
}

void SoundGame::StopBackGame()
{
	SBackGame->Stop();
}
