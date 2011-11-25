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
};

