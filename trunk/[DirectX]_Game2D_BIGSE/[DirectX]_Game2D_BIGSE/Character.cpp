#include "Character.h"
#include "RSMainGame.h"
#include "Global.h"
#include "Frenzy.h"
#include "CallPet.h"

Character::Character(void)
{

	m_HP = 20; 
	m_Damage = 1;
}


Character::~Character(void)
{
}

void Character::ActiveSkill(int _Index){
	
	m_skillManager->ActiveSkill(_Index,m_X,m_Y,m_Dir);
	if (m_Vy < 0) //nhay len
	{
		m_Vy = fabs (m_Vy);
	}
}
void Character::Init(){
	m_SCharater = RSMainGame::get()->getCharacter();
	m_InfoSprite.setSize(300,200);
	m_STT = ACTIVE;

	m_skillManager = new SkillManager();
	m_skillManager->AddSkill(new Skill());
	m_skillManager->AddSkill(new Frenzy());
	m_skillManager->AddSkill(new CallPet());
}

bool Character::iCollision(MyObject* _Obj){
	return false;
}

void Character::ProcessCollision(MyObject* _Obj){
	m_skillManager->ProcessCollision(_Obj);
}
void Character::Move(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight){	

	float NextX,NextY;
	
	#pragma region RIGHT
if (m_Vx > 0){
		NextX =m_X + _Time* g_VX; //thoi gian thuc
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
		if (m_Vx<0){

			NextX= m_X - _Time* g_VX;
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
		m_Vx = 0;
	}
	

	#pragma region DOWN
m_Vy+= _Time*g_GAVITY;
	NextY = m_Y + m_Vy*_Time + 0.5*(_Time*_Time)*g_GAVITY;
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
		
}

void Character::UpdateStatus(float _Time)
{
	 if(!m_iActive )
	 {
		 m_TimeUpdate += _Time;
		 if(m_TimeUpdate > 1 )
		 {
			 m_iActive = true ;
			 m_TimeUpdate =0;

		 }

	 }
}

void Character::Update(float _Time, int** _Terrain,float _MaxWidth,float _MaxHeight)
{
	Animation(_Time);
	Move(_Time,_Terrain,_MaxWidth,_MaxHeight);	
	UpdateStatus(_Time);

	m_skillManager->Update(_Time,_Terrain,_MaxWidth,_MaxHeight);
}

void Character::Draw(D3DXMATRIX _MWorld,LPD3DXSPRITE _Handler)
{
	if(getLife() == false)
	{
		return ;
	}

	m_skillManager->Draw(_MWorld,_Handler);

	if( getActive() ==false)
	{
		if (timeGetTime()%400 >200)
		{
			return ;
		}
	}
	if (m_skillManager->getSkill(0)->getSTT()==ACTIVE)
	{
		m_InfoSprite.setCurFrame(m_skillManager->getSkill(0)->getInfoSprite().getCurFrame());
	}

		if (m_Dir<0){
			m_InfoSprite.setScaleX(1);
		}else{
			m_InfoSprite.setScaleX(-1);
		}
		m_InfoSprite.setXY(-125+m_X,-54+m_Y);

		m_SCharater->Draw(_MWorld,m_InfoSprite,_Handler);
		
}

void Character::Release(){

}

void Character::setMove(int _move){
	/*if(m_HIT->getSTT()!= ACTIVE){*/
		m_Vx = _move;
		m_Dir = _move;
	/*}*/
}

void Character::setJump(){

	if ((m_Vy== 0) && (m_skillManager->getSkill(0)->getSTT()!= ACTIVE))
	{
		m_Vy = -1* g_VY_JUMP;
	}
}