#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class iState;
class iPlay
{
protected:
	/* Current State */
	iState* m_CurState;

	/* Next State */
	iState* m_NextState;

	/* Graphics device */
	LPDIRECT3DDEVICE9 m_Device;
public:
	iPlay(LPDIRECT3DDEVICE9 Device);
	virtual ~iPlay(void);
	void SetCurState (iState* _curstate);
	void SetNextState (iState* _nextstate);
	iState* GetCurState ();
	iState* GetNextState ();
	void SetDevice (LPDIRECT3DDEVICE9 Device);
	LPDIRECT3DDEVICE9 GetDevice ();
	virtual void Init ()=0;
	virtual void Update (float _Time)=0;
	virtual void Draw ()=0;
	virtual void Release ()=0;
};



