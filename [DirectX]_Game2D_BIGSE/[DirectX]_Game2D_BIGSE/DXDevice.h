#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class DXDevice
{
	LPDIRECT3D9 m_pD3D;
	D3DPRESENT_PARAMETERS m_pD3DPP,mpp;
	LPDIRECT3DDEVICE9 m_pD3DDev;
	LPDIRECT3DSURFACE9 m_pBackBuffer;	
public:


	DXDevice(void);
	~DXDevice(void);
	bool Create_DirectX ();
	bool Create_Para (bool _iFullmode,HWND _hwnd);
	bool Create_Device (HWND _hwnd);
	void CreateBuffer ();

	void Init (HWND _hwnd,bool _iFullmode)
	{
		Create_DirectX ();
		Create_Para ( _iFullmode, _hwnd);
		Create_Device ( _hwnd);
		CreateBuffer ();
	}
	LPDIRECT3DDEVICE9 getDevice ()
	{
		return m_pD3DDev;
	}
	LPDIRECT3DSURFACE9 getBackBuffer ()
	{
		return m_pBackBuffer;
	}
	LPDIRECT3DSURFACE9 LoadSurface(char*,D3DCOLOR);
	void Release ();

};

