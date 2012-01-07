#pragma once
#include <d3dx9.h>
class InfoSprite
{
public:
	/* Position to render */
	float m_X,m_Y;

	/* Size Image */
	float m_Width,m_Height;

	/* Depth 0~1 */
	float m_Depth;

	/* Current frame */
	int m_CurFrame;

	/* Zoom image ( Negative value to mirror) */
	float m_ScaleX,m_ScaleY;

	/* Rotation image ( Degree ) */
	float m_Rotation;

	/* Color to blending ( include Alpha ) */
	D3DXCOLOR m_Color;

	InfoSprite(void);
	~InfoSprite(void);
	void setX (float _X){
		m_X = _X;
	}
	void setY (float _Y){
		m_Y = _Y;
	}
	void setXY (float _X, float _Y){
		m_X = _X;
		m_Y = _Y;
	}
	void setSize (float _Width, float _Height){
		m_Width = _Width;
		m_Height = _Height;
	}
	/* Depth sprite (0.0f ~ 1.0f) */
	void setDepth (float _Depth){
		m_Depth = _Depth;
	}

	/* Scale sprite (Negative value to mirror) */
	void setScaleX (float _ScaleX){
		m_ScaleX = _ScaleX;
	}
	/* Scale sprite (Negative value to mirror) */
	void setScaleY (float _ScaleY){
		m_ScaleY = _ScaleY;
	}
	/* Scale sprite (Negative value to mirror) */
	void setScaleXY (float _ScaleX,float _ScaleY){
		m_ScaleX = _ScaleX;
		m_ScaleY = _ScaleY;
	}
	/* Rotation sprite (value is degree) */
	void setRotation (float _Rotation){
		m_Rotation = _Rotation;
	}
	/* Set red color (0.0f ~ 1.0f)*/
	void setColorRed (float _red){
		m_Color.r = _red;
	}
	/* Set blue color (0.0f ~ 1.0f)*/
	void setColorBlue (float _blue){
		m_Color.b = _blue;
	}
	/* Set green color (0.0f ~ 1.0f)*/
	void setColorGreen (float _green){
		m_Color.g = _green;
	}
	/* Set alpha color (0.0f ~ 1.0f)*/
	void setColorAlpha (float _alpha){
		m_Color.a = _alpha;
	}
	/* Set  color (0.0f ~ 1.0f)
	red, blue, green, alpha	*/
	void setColor (float _red,float _blue,
		float _green,float _alpha){
		m_Color.a	= _alpha;
		m_Color.r	= _red;
		m_Color.b	= _blue;
		m_Color.g	= _green;
	}

	void setCurFrame (int _curframe){
		m_CurFrame	= _curframe;
	}

	/* Animation frame 
	First to First + _offset 
	*/
	void NextFrame (int _first, int _offset){
		if (m_CurFrame<_first)
		{
			m_CurFrame = _first;
		}else{
			if(m_CurFrame>(_first+ _offset)){
				m_CurFrame = _first+ _offset;
			}else{
				m_CurFrame++;
				if (m_CurFrame>= _first+ _offset)
				{
					m_CurFrame = _first;
				}
			}
		}
		/*m_CurFrame = abs((m_CurFrame+1)%(_offset)) + _first;*/
	}
	void BackFrame(int _first, int _offset)
	{
		if(m_CurFrame > _first)
		{
			m_CurFrame = _first;
		}
		else{
			if(m_CurFrame < ( _first -  _offset))
			{
				m_CurFrame = _first - _offset ;
			}
			else {
				m_CurFrame --;
				if(m_CurFrame <= _first - _offset)
				{
					m_CurFrame = _first;
				}
			}
		}
	}

	float getX () { return m_X;}
	float getY () { return m_Y;}

	int getCurFrame () {return m_CurFrame;}

	float getScaleX () {return m_ScaleX;}
	float getScaleY () {return m_ScaleY;}

	D3DXVECTOR2 getScale () {return D3DXVECTOR2(m_ScaleX,m_ScaleY);}

	/* Rotation (Degree) */
	float getRotation () {return m_Rotation;}

	D3DXCOLOR getColor () {return m_Color;}

	float getDepth () {return m_Depth;}

	D3DXMATRIX getMatrixTransform () // bien doi truc toa do thut. lui`
	{
		D3DXMATRIX MaTrix; //
		
		D3DXVECTOR2 Center((float)((m_Width)/2),(float)((m_Height)/2));//
		D3DXVECTOR2 MTScale(m_ScaleX,m_ScaleY); //
		D3DXVECTOR2 MTTran (m_X,m_Y); 
		float Rota = (float)(m_Rotation*2*D3DX_PI)/(float)(360);

		D3DXMatrixTransformation2D(&MaTrix,&Center,0,&MTScale,&Center,Rota,&MTTran);
		return MaTrix;
	}
};

