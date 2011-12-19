#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
class RSMainGame
{
private:
	static RSMainGame* instance ; 
	Sprite* m_Character;
	Sprite* m_Terrain;
	Sprite* m_Frenzy;
	Sprite* m_Pet ;
	Sprite* m_Archer ;
	Sprite* m_Arrow ;
	Sprite* m_Magician;
	Sprite* m_medicine;
	Sprite* m_Partner;
	Sprite* m_Angle ;
	Sprite* m_Thunder1;
	Sprite* m_Thunder2;
	RSMainGame(void);
public:
	
	~RSMainGame(void);
	static RSMainGame* get (){
		if (instance == NULL)
		{
			instance = new RSMainGame();
		}
		return instance;
	}
	void IntRS (LPDIRECT3DDEVICE9 _Device);
	void Release ();

	Sprite* getCharacter (){
		return m_Character;
	}
	Sprite* getTerrain (){
		return m_Terrain;
	}
	Sprite* getFrenzy(){
		return m_Frenzy;
	}
	Sprite* getPet(){
		return m_Pet;
	}
	Sprite* getArcher(){
		return m_Archer ;
	}
	Sprite* getArrow(){
		return m_Arrow ;
	}
	Sprite* getMagician(){
		return m_Magician ;
	}
	Sprite* getMedicine()
	{
		return m_medicine;
	}
	Sprite* getPartner()
	{
		return  m_Partner;
	}
	Sprite* getAngle()
	{
		return  m_Angle;
	}
	Sprite* getThunder1()
	{
		return  m_Thunder1;
	}
	Sprite* getThunder2()
	{
		return  m_Thunder2;
	}
};

