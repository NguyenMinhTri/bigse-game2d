#include "Sprite.h"
#include <string>
#include <d3d9types.h>
#include "InfoSprite.h"
#include "Global.h"


Sprite::Sprite(LPDIRECT3DDEVICE9 _Device,char* filename,int _width,int _height,
	int _col,D3DCOLOR _tran )
{
	
	
	m_Width = _width;
	m_Height = _height;
	m_ColFrame = _col;
	
	//////////////////////////////////////////////////////////////////////////
	D3DXIMAGE_INFO info; 
	HRESULT result; 
	result = D3DXGetImageInfoFromFile(filename,&info);
	if (result!=D3D_OK)
	{
		return;
	}
	result = D3DXCreateTextureFromFileEx(_Device,(filename),	info.Width,	info.Height,
		1,D3DUSAGE_DYNAMIC,	D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT,D3DX_DEFAULT,
		D3DX_DEFAULT,_tran,	&info,	NULL,&m_Image);
	if (result!=D3D_OK) 
	{
		return;
	}
}

Sprite::~Sprite(void)
{
	m_Image->Release();
}
void Sprite::Transform(LPD3DXSPRITE Sprite_Handler)
{

}
RECT Sprite::getRect(int Curframe)
{
	RECT rect;
	rect.top = (Curframe/m_ColFrame)*m_Height;
	rect.bottom = rect.top + m_Height;
	rect.left = (Curframe%m_ColFrame)*m_Width;
	rect.right = rect.left + m_Width;
	return rect;
}
void Sprite::Draw(float X,float Y,int Index,LPD3DXSPRITE _Handler)
{
	
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	_Handler->SetTransform(&m);

	_Handler->Draw(m_Image,&this->getRect(Index),
		NULL,&D3DXVECTOR3(X,Y,0),D3DCOLOR_ARGB(255,255,255,255));
}

void Sprite::Draw(InfoSprite _info,LPD3DXSPRITE _Handler){

	
	_Handler->SetTransform(&_info.getMatrixTransform());

	_Handler->Draw(m_Image,&this->getRect(_info.getCurFrame()),NULL,
		&D3DXVECTOR3(0,0,_info.getDepth()),_info.getColor());

	
}

void Sprite::Draw(D3DMATRIX _World,InfoSprite _info,LPD3DXSPRITE _Handler)
{
	
	D3DXMATRIX ma;
	ma = _info.getMatrixTransform()*_World;
	_Handler->SetTransform(&ma);

	_Handler->Draw(m_Image,&this->getRect(_info.getCurFrame()),NULL,
		&D3DXVECTOR3(0,0,_info.getDepth()),_info.getColor());
}