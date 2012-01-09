#include "Item.h"
#include "RSMainGame.h"
#include "Global.h"

Item::Item(void)
{
	
	Init();
}
Item :: Item(float x,float y)
{
	m_X = x;
	m_Y = y;
	Init();
}


Item::~Item(void)
{
}

void Item :: Init()
{
	setLife(true);
	m_effect = 500 ;
	m_STT = ACTIVE;
	m_Item = RSMainGame::get()->getItemHealth();
	m_InfoSprite.setSize(85,78);
	setSize(85,78);
}

bool Item::iCollision(MyObject* _Obj){
	return false;
}


void Item::ProcessCollision(MyObject* _Obj)
{
	if(getRect().iCollision(_Obj->getRect()))
 	{
       _Obj->setHp(_Obj->getHp() + m_effect);
		  setLife(false);
	}
}

void Item ::Animation(float _Time)
{
	if(m_STT == ACTIVE)
	{
		m_TimeAni +=_Time ;
		if(m_TimeAni >= 0.13f)
		{
			m_TimeAni -=0.13f;
			m_InfoSprite.NextFrame(0,4) ;
		}
	}
}

void Item::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	m_InfoSprite.setXY(m_X,m_Y);
	m_Item->Draw(_MWorld,m_InfoSprite,_Handler);
}

void Item ::UpdateStatus(float _Time)
{

}
void Item ::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	Move(_Time,_Terrain,_MaxWidth,_MaxHeight);
}
void Item ::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	float NextX,NextY;
#pragma region DOWN
	m_Vy+= _Time*m_Gravity;
	NextY = m_Y + m_Vy*_Time + 0.5*(_Time*_Time)*m_Gravity;
	if (NextY >= (_MaxHeight - m_Height))
	{
		NextY =  _MaxHeight - m_Height;
	}
	if (NextY <= 0)
	{
		NextY = 0;
		m_Vy = fabs(m_Vy);
	}

	if (m_Vy >= 0){

		bool iColTer = false;
		for (int j = (m_Y+m_Height)/g_CELL; j <  (NextY+m_Height)/g_CELL ;j++){
			for (int i = m_X/g_CELL;i < (m_X+m_Width)/g_CELL;i++ ){
				if (_Terrain[i][j]!=0){
					iColTer = true;
					m_Y = g_CELL * (j) - m_Height;
					m_Vy = 0;
					break;
				}
			}
			if (iColTer == true){
				break;
			}
		}
		if (iColTer == false){
			m_Y = NextY;
		}
#pragma endregion DOWN
	}

}
void Item :: Release()
{

}