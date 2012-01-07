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
	
	void StopBackGame ();
	
};
extern SoundGame* SouGa;
#endif