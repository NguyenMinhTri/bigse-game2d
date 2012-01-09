#ifndef _SOUNDGAME_H_
#define _SOUNDGAME_H_
#include "Global.h"
#include "SoundDev.h"
#include "DXManager.h"
class SoundGame
{
private:
	static SoundGame* m_Instance;
	HWND phwnd;
	DSound* SDev;
	bool SActi,BackActi,EffActi;
	
	CSound* SBackGame;
	CSound* basicbeam_fire ;
	CSound* m_Hero3;
	CSound* m_SoloFlare ;
	CSound* m_kamehame ;
	CSound* m_Laze ;
	CSound* m_GodLike_Scream ;
	CSound* m_GodLike_Punch ;
	CSound* m_XetXet ;
	CSound* m_Thunder ;
	CSound* m_Pharaon ;
	CSound* m_AngleXetXet;
	CSound* m_MusicPlayer ;
	CSound* m_State_Play ;
	SoundGame();
	
public:
	~SoundGame();
	static SoundGame* Instance()
	{
		if (m_Instance==NULL)
		{
			m_Instance = new SoundGame();
			m_Instance->Init(DXManager::Instance()->getHWND());
		}
		return m_Instance;
	}
	void SetSound (bool _val);
	void SetSoundBackGround (bool _val);
	void SetSoundEffect (bool _val) ;
	bool GetSound () {return SActi;}
	
void Init(HWND _hwnd);
	
	void PlayBackGame ();
	void PlayEffect ();
	void PlayBeam_Fire();
	void PlayHero_3() ;
	void PlaySolarFlare();
	void PlayKaMeHaMe() ;
	void PlayLaze();
	void PlayGLScream() ;
	void PlayGLPunch();
	void PlayXetXet();
	void PlayThunder();
	void PlayPharaon();
	void PlayAngleXetXet() ;
	void PlayMusicPlayer();
	void PlayStatePlay() ;
	void StopBackGame ();
	void StopMainMeNu() ;
	void StopSoundSetting();
	void PlaySoundSetting();
};
extern SoundGame* SouGa;
#endif