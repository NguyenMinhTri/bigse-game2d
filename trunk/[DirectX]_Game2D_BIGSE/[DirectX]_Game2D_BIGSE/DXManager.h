#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class DXManager
{
	static DXManager* m_Instance;
	LPDIRECT3DDEVICE9 m_pD3DDev;
	HWND m_HWND;
	DXManager(void);
public:
	
	~DXManager(void);
	static DXManager* Instance()
	{
		if (m_Instance==NULL)
		{
			m_Instance = new DXManager();
		}
		return m_Instance;
	}
	void setDevice (LPDIRECT3DDEVICE9 _pD3DDev)
	{
		m_pD3DDev = _pD3DDev;
	}
	LPDIRECT3DDEVICE9 getDevice ()
	{
		return m_pD3DDev;
	}
	void setHWND (HWND _hWnd)
	{
		m_HWND = _hWnd;
	}
	HWND getHWND ()
	{
		return m_HWND;
	}
};

