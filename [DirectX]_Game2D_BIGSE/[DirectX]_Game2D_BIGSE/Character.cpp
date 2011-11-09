#include "Character.h"
#include "RSMainGame.h"
#include "Global.h"


Character::Character(void)
{
	
}


Character::~Character(void)
{
}

void Character::ActiveSkill(){
	
	m_HIT->Active(m_X,m_Y,m_Dir);
	if (m_Vy < 0)
	{
		m_Vy = fabs (m_Vy);
	}
}
void Character::Init(){
	m_SCharater = RSMainGame::get()->getCharacter();
	m_InfoSprite.setSize(300,200);
	m_STT = ACTIVE;

	m_HIT = new Skill();
	m_HIT->Init();

}

bool Character::iCollision(MyObject* _Obj){
	return false;
}

void Character::ProcessCollision(MyObject* _Obj){

}
void Character::Move(float _Time, int** _Terrain){
	if(m_HIT->getSTT()== ACTIVE) return;

	float NextX,NextY;
	
	#pragma region RIGHT
if (m_Vx > 0){
		NextX =m_X + _Time* g_VX;
		

			bool iColTer = false;
			for (int i = (m_X+m_Width)/g_CELL; i <  (NextX+m_Width)/g_CELL;i++){
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
		if (m_Vx<0){

			NextX= m_X - _Time* g_VX;
			int n = (NextX/g_CELL);
			int m = (m_X/g_CELL);
			if (n!=m ){

				bool iColTer = false;
				for (int i = m_X/g_CELL-1; i >  NextX/g_CELL-1;i--){
					for (int j = m_Y/g_CELL;j < int((m_Y+m_Height-1)/g_CELL) +1;j++ ){
						if (_Terrain[i][j]!=0){
							iColTer = true;
							m_X = g_CELL * (i+1);
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

			}else{
				m_X = NextX;
			}
			
		}		
	}
#pragma endregion LEFT

	if (m_Vy==0)
	{
		m_Vx = 0;
	}
	

	#pragma region DOWN
m_Vy+= _Time*g_GAVITY;
	NextY = m_Y + m_Vy*_Time/* + 0.5*(_Time*_Time)*g_GAVITY*/;

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

void Character::Animation(float _Time){
	m_TimeAni += _Time ;
	switch (m_STT)
	{
	case ACTIVE:
		if (m_TimeAni>= 0.15f)
		{
			m_TimeAni -= 0.15f;

			if (m_Vy != 0){
				m_InfoSprite.setCurFrame(4);
			}else{
				if (m_Vx == 0){
					m_InfoSprite.NextFrame(8,4);
				} 
				else{
					m_InfoSprite.NextFrame(0,4);
				}
			}
		}
		break;
	}

	m_HIT->Animation(_Time);
}

void Character::UpdateStatus(float _Time){

}

void Character::Update(float _Time){

}

void Character::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler){
	
	if (m_HIT->getSTT()==ACTIVE){

		m_HIT->Draw(_MWorld,_Handler);
	}else{

		if (m_Dir<0){
			m_InfoSprite.setScaleX(1);
		}else{
			m_InfoSprite.setScaleX(-1);
		}
		m_InfoSprite.setXY(-125+m_X,-54+m_Y);
		m_SCharater->Draw(m_InfoSprite,_Handler);
	}
	

}

void Character::Release(){

}

void Character::setMove(int _move){
	if(m_HIT->getSTT()!= ACTIVE){
		m_Vx = _move;
		m_Dir = _move;
	}
}

void Character::setJump(){

	if ((m_Vy== 0) && (m_HIT->getSTT()!= ACTIVE))
	{
		m_Vy = -1* g_VY_JUMP;
	}
}