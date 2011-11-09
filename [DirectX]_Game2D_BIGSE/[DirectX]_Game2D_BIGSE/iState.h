#ifndef _IPLAY_H_
#define _IPLAY_H_
#include "iPlay.h"
#include <dinput.h>
class iState
{
protected:
	/*  ID state */
	int m_ID;

	/*  i play control all state */
	iPlay* m_iPlay;

	/* graphics device */
	LPDIRECT3DDEVICE9 m_Device;
public:
	iState(iPlay* GamePlay);
	virtual ~iState(void);
	void SetIDState (int _Id);
	void SetGamePlay (iPlay* GamePlay);
	int GetIDState ();
	iPlay* GetGamePlay ();
	virtual void IsKeyDown(int KeyCode){};
	virtual void OnKeyDown(int KeyCode){};
	virtual void OnKeyUp(int KeyCode){};
	virtual void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon){};
	virtual void Init () =0;
	virtual void Update (float _Time) =0;
	virtual void Draw () =0;
	virtual void Release () =0;
};
#endif