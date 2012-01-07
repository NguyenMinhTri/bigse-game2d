#include "Camera.h"


Camera::Camera(void)
{
}
Camera::Camera(float _X, float _Y,float _Width,float _Height)
{
	m_X = _X;
	m_Y = _Y;
	m_Width = _Width;
	m_Height = _Height;
	m_Dy = 0;
	m_VDy = 1;
	m_SC = 1;
	m_Offset = 200;
}

Camera::~Camera(void)
{
}
void  Camera::Update(Character* _Character,float _MaxWidth,float _MaxHeight)
{
	m_X = _Character->getX() - (g_SCREEN_WIDTH - _Character->getWidth())/2 ;
	if (m_X<=0)
	{
		m_X = 0;
	}
	if (m_X >= (_MaxWidth-m_Width))
	{
		m_X = (_MaxWidth-m_Width)-1;
	}
	m_Y = _Character->getY() - (g_SCREEN_HEIGHT - _Character->getHeight())/2 ;
	if (m_Y<=0)
	{
		m_Y = 0;
	}
	if (m_Y >= (_MaxHeight-m_Height))
	{
		m_Y = (_MaxHeight-m_Height)-1;
	}
}

void Camera::UpdateEffect(float _Time)
{
	if (timeGetTime()%400 >200)
	{
		m_Dy = 3;
	} 
	else
	{
		m_Dy = -3;
	}
	m_SC += m_VDy*0.3*_Time;
	if (m_SC > 1.1f)
	{
		m_VDy = -1;
	} 
	if(m_SC<1)
	{
		m_VDy = 1;
	}

}

D3DXMATRIX Camera::getMatrixTransform ()
{
	D3DXMATRIX mtFinal,mtCamera,mtEffect;

	D3DXVECTOR2 CenterEffect (m_X + g_SCREEN_WIDTH/2,m_Y +g_SCREEN_HEIGHT/2);
	D3DXVECTOR2 TranEffect (0,0); 
	D3DXVECTOR2 ShakeEffect(m_Dy,0);
	D3DXVECTOR2 ScaleEffect (m_SC,m_SC);
	D3DXMatrixTransformation2D(&mtEffect,&CenterEffect,1,&ScaleEffect,NULL,NULL,&TranEffect);

	D3DXVECTOR2 TransCamera (-m_X,-m_Y); //
	D3DXMatrixTransformation2D(&mtCamera,NULL,0,NULL,NULL,NULL,&TransCamera);

	mtFinal = mtEffect*mtCamera;
	return mtFinal;		
}