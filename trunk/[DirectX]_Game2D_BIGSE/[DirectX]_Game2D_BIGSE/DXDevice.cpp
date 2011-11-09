#include "DXDevice.h"
#include "Global.h"


DXDevice::DXDevice(void)
{
}


DXDevice::~DXDevice(void)
{
}

bool DXDevice::Create_DirectX ()
{
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if (!m_pD3D) 
	{
		MessageBox( NULL,"No compatible Direct3D object could be created.",
			"Fatal Error!",MB_OK | MB_ICONSTOP | MB_APPLMODAL );
		return false;
	}
	return true;
}
bool DXDevice::Create_Para (bool _iFullmode,HWND _hwnd)
{
	// Fill out a simple set of present parameters
	ZeroMemory( &m_pD3DPP, sizeof(m_pD3DPP) );

	m_pD3DPP.BackBufferHeight			= g_SCREEN_HEIGHT;
	m_pD3DPP.BackBufferWidth			= g_SCREEN_WIDTH;
	m_pD3DPP.BackBufferFormat           = D3DFMT_A8R8G8B8;
	m_pD3DPP.BackBufferCount            = 1;
	m_pD3DPP.MultiSampleType            = D3DMULTISAMPLE_NONE;
	m_pD3DPP.MultiSampleQuality         = 0;
	m_pD3DPP.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	m_pD3DPP.hDeviceWindow              = _hwnd;
	m_pD3DPP.Windowed                   = !_iFullmode;
	m_pD3DPP.EnableAutoDepthStencil     = true; 
	m_pD3DPP.AutoDepthStencilFormat     = D3DFMT_D24S8;
	m_pD3DPP.Flags                      = 0;
	m_pD3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_pD3DPP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	mpp = m_pD3DPP;
	return true;
}
bool DXDevice::Create_Device (HWND _hwnd)
{
	m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_pD3DPP, &m_pD3DDev);
	if (m_pD3DDev == NULL )
	{
		MessageBox(_hwnd,"Count Create device with D3DDEVTYPE_HAL & D3DCREATE_HARDWARE_VERTEXPROCESSING \n Try again !!! ","Warning!!",MB_OK);
		m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_pD3DPP, &m_pD3DDev);
		if (m_pD3DDev == NULL )
		{
			MessageBox(_hwnd,"Count Create device with D3DDEVTYPE_HAL & D3DCREATE_SOFTWARE_VERTEXPROCESSING /n Try again !!! ","Warning!!",MB_OK);
			m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
				_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_pD3DPP, &m_pD3DDev);
			if (m_pD3DDev == NULL )
			{
				MessageBox(_hwnd,"Count Create device with D3DDEVTYPE_REF & D3DCREATE_SOFTWARE_VERTEXPROCESSING /n Try again !!! ","Warning!!",MB_OK);
				m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_SW,
					_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&m_pD3DPP, &m_pD3DDev);
				if (m_pD3DDev == NULL )
				{
					MessageBox(_hwnd,"Count Create device with D3DDEVTYPE_SW & D3DCREATE_SOFTWARE_VERTEXPROCESSING /n Try again !!! ","Warning!!",MB_OK);
					return false;
				} 

			} 	

		} 	
	} 		 
	return true;
}
void DXDevice::CreateBuffer()
{
	m_pD3DDev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&m_pBackBuffer);
}
void DXDevice::Release ()
{
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
	}
	if (m_pD3DDev != NULL)
	{
		m_pD3DDev->Release();
	}	
	if (m_pBackBuffer != NULL)
	{
		m_pBackBuffer->Release();
	}
}
LPDIRECT3DSURFACE9 DXDevice::LoadSurface(char *filename,D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image=NULL;
	D3DXIMAGE_INFO info;
	LRESULT result;
	result=D3DXGetImageInfoFromFile(filename,&info);
	if(result!=D3D_OK)
	{
		MessageBox(NULL,"Couldn't Get information image","Error",MB_OK);
		return NULL;
	}
	result=m_pD3DDev->CreateOffscreenPlainSurface(
		info.Width,info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&image,NULL);
	if(result!=D3D_OK)
	{
		MessageBox(NULL,"Couldn't create surface image","Error",MB_OK);
		return NULL;
	}
	result=D3DXLoadSurfaceFromFile(
		image,NULL,NULL,filename,NULL,D3DX_DEFAULT,transcolor,NULL);
	if(result!=D3D_OK)
	{
		MessageBox(NULL,"Couldn't load image from file","Error",MB_OK);
		return 0;
	}
	return image;
}