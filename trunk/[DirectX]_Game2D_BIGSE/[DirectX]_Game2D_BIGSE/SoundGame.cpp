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
	SActi=true;
	SBackGame = SDev->LoadSound("data\\sound\\sback.wav");
	basicbeam_fire = SDev->LoadSound("data\\sound\\basicbeam_fire.wav");
	m_Hero3 =  SDev->LoadSound("data\\sound\\scream2.wav");
	m_SoloFlare =  SDev->LoadSound("data\\sound\\solarflare.wav");
	m_kamehame = SDev->LoadSound("data\\sound\\kamehame.wav");
	m_Laze = SDev->LoadSound("data\\sound\\Laze.wav");
	m_GodLike_Scream = SDev->LoadSound("data\\sound\\scream.wav");
	m_GodLike_Punch = SDev->LoadSound("data\\sound\\specialbeamcannon.wav");
	m_XetXet= SDev->LoadSound("data\\sound\\strongkick.wav");
	m_Thunder = SDev->LoadSound("data\\sound\\thunderclap2.wav");
	m_Pharaon = SDev->LoadSound("data\\sound\\Pharaon.wav");
	m_AngleXetXet = SDev->LoadSound("data\\sound\\teleport.wav");
	m_MusicPlayer = SDev->LoadSound("data\\sound\\MusicChoosePlayer.wav");
	m_State_Play = SDev->LoadSound("data\\sound\\SkyForest.wav");
}

void SoundGame::PlayBackGame()
{
	
	if (BackActi)
	{
		SBackGame->Play(0,DSBPLAY_LOOPING);
	}
	else
		SBackGame->Stop();
}
void SoundGame::PlayEffect()
{
	if (EffActi)
	{
		//SPerffect->Play();
	}
}

void SoundGame ::PlayBeam_Fire ()
{
	if(EffActi)
	{
		basicbeam_fire->Play();
	}

}
void SoundGame :: PlayHero_3()
{
	if(EffActi)
	{
		m_Hero3->Play();
	}

}
void SoundGame ::PlaySolarFlare()
{
	if(EffActi)
	{
		m_SoloFlare->Play();
	}
	else m_SoloFlare->Stop();
}
void SoundGame :: PlayKaMeHaMe()
{
	if(EffActi)
	{
		m_kamehame->Play();
	}
}
void SoundGame :: PlayLaze()
{
	if(EffActi)
	{
		m_Laze->Play() ;
	}
}
void SoundGame ::PlayGLScream()
{
	if(EffActi)
	{
		m_GodLike_Scream->Play() ;
	}
}
void SoundGame :: PlayGLPunch()
{
	if(EffActi)
	{
		m_GodLike_Punch->Play() ;
	}
}
void SoundGame :: PlayXetXet()
{
	if(EffActi)
	{
		m_XetXet->Play();
	}
}
void SoundGame ::PlayAngleXetXet()
{
	if(EffActi)
	{
		m_AngleXetXet->Play();
	}
}
void SoundGame :: PlayThunder()
{
	if(EffActi)
	{
		m_Thunder->Play();
	}
}
void SoundGame :: PlayPharaon()
{
	if(EffActi)
	{
		m_Pharaon->Play();
	}
}
void SoundGame :: PlayMusicPlayer()
{
	if(EffActi)
	{
		m_MusicPlayer->Play();
	}
}
void SoundGame ::PlayStatePlay()
{
	if(EffActi)
	{
		m_State_Play->Play();
	}
}
void SoundGame::StopBackGame() 
{
	SBackGame->Stop();
}

void SoundGame::StopSoundSetting()
{
	SBackGame->Stop();
}
void SoundGame :: StopMainMeNu()
{
	SBackGame->Stop() ;
	m_MusicPlayer->Stop();
	m_State_Play->Stop() ;
}

void SoundGame::PlaySoundSetting()
{
	SBackGame->Play(0,DSBPLAY_LOOPING);
}