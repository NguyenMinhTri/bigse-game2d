#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <d3d9.h>
#include <d3dx9.h>
#include <stdlib.h>
#include <stdio.h>
#include "InfoSprite.h"

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 m_Image;		
	int m_CurFrame,m_ColFrame;

	float m_Width,m_Height;

public:
	Sprite(LPDIRECT3DDEVICE9 Device,char* filename,int _width,int _height,int _col,D3DCOLOR _tran = D3DCOLOR_XRGB(255,0,255));
	virtual ~Sprite();
	void SetImage (LPDIRECT3DTEXTURE9 Image){m_Image = Image;};
	
	void SetSize (float _With,float _Height) {
		m_Width	= _With;
		m_Height= _Height;
	}
	void SetColum (int ColFrame) {m_ColFrame = ColFrame;};
	void SetCurFrame (int CurFrame) {m_CurFrame=CurFrame;};	
	
	LPDIRECT3DTEXTURE9 GetImage (){return m_Image;};
	
	int GetColumFrame () {return m_ColFrame;};
	int GetCurFrame () {return m_CurFrame;}	
	
	RECT getRect (int Curframe);
	void Draw (LPD3DXSPRITE _Handler,D3DMATRIX _mtWorld, float _X,float _Y, int _Index,
		float _depth = 0.0f,D3DXCOLOR _color =D3DXCOLOR(1,1,1,1));
	void Draw (float X,float Y,int Index,LPD3DXSPRITE Sprite_Handler);
	void Draw (D3DMATRIX _World,InfoSprite _info,LPD3DXSPRITE _Handler);
	void Draw (InfoSprite _info,LPD3DXSPRITE _Handler);
};
#endif