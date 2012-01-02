#include "MyObject.h"
#include "Global.h"


MyObject::MyObject(void)
{
	m_X			= 0;
	m_Y			= 0;
	m_Width		= 0;
	m_Height	= 0;
	m_Vx		= g_VX;
	m_Vy		= 0;
	m_Direct	= 0;
	m_Gravity	= g_GRAVITY;
	m_TimeUpdate= 0;
	m_TimeAni	= 0;
	m_TimePrivate = 0;

	m_iFrenzy = false;
    m_iFire = false ;
	m_iLife = true;
	m_iActive = true;
	m_iThunder = false ;

	m_ID		= PLAYER;
	m_STT		= ACTIVE;
	m_OldSTT	= ACTIVE;
}


MyObject::~MyObject(void)
{

}

void MyObject::setMove(int _move)
{
	m_VxDirect = _move;
	m_Direct = _move;
}

void MyObject::setJump()
{	
	if(m_Vy!= 0) return;
	m_Vy = -1* g_VY_JUMP;	
}

void MyObject::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{	
	if(m_iFrenzy ==false)
	{
		float NextX,NextY;

#pragma region RIGHT
	if (m_VxDirect > 0){
		NextX =m_X + _Time* m_Vx; //thoi gian thuc
		if (NextX >= _MaxWidth - m_Width)
		{
			NextX = _MaxWidth - m_Width;
		}

		bool iColTer = false;
		for (int i = (m_X + m_Width)/g_CELL ; i <  (NextX+m_Width)/g_CELL;i++)
		{
			for (int j = m_Y/g_CELL;j < (int)((m_Y+m_Height-1)/g_CELL) +1;j++ ){
				if (_Terrain[i][j]!=0){
					iColTer = true;
					m_X = g_CELL * (i) - m_Width;
					break;
				}
			}
			if (iColTer == true){
				break;
			}
		}

		if (iColTer == false){
			m_X = NextX;
		}

#pragma endregion RIGHT

#pragma region LEFT
	}else{
		if (m_VxDirect<0){

			NextX= m_X - _Time* m_Vx;
			if (NextX <= 0)
			{
				NextX = 0;
			}
			bool iColTer = false;
			for (int i = m_X/g_CELL-1; i >  NextX/g_CELL-1;i--) // 
			{
				for (int j = m_Y/g_CELL ;j < int((m_Y+m_Height-1)/g_CELL) +1 ; j++ )
				{
					if (_Terrain[i][j]!=0){
						iColTer = true;
						m_X = g_CELL * (i+1);
						break;
					}
				} 
				if (iColTer == true)
				{
					break;
				}
			}

			if (iColTer == false)
			{
				m_X = NextX;
			}

		}		
	}
#pragma endregion LEFT

	if (m_Vy==0)
	{
		m_VxDirect = 0;
	}


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

#pragma region UP
	}else{

		NextY = m_Y + m_Vy* _Time;
		int n = (NextY/g_CELL);
		int m = (m_Y/g_CELL);
		if (n!=m ){

			bool iColTer = false;
			for (int j = m_Y/g_CELL-1; j >  NextY/g_CELL-1;j--){
				for (int i = m_X/g_CELL;i < (m_X+m_Width)/g_CELL;i++ ){
					if (_Terrain[i][j]!=0){
						iColTer = true;
						m_Y = g_CELL * (j+1);
						m_Vy = fabs(m_Vy);
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

		}else{
			m_Y = NextY;
		}
	}
#pragma endregion UP
	}
}