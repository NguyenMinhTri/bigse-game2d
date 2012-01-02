#include "EffectFont.h"
#include "RSMainGame.h"


EffectFont::EffectFont(float _X, float _Y,int _Damage)
{
	m_X = _X;
	m_Y = _Y;
	Init();
	m_Damage = _Damage;


}


EffectFont::~EffectFont(void)
{
}
void EffectFont::Init()
{

	m_InfoSprite.setSize(37,39);
	m_Sprite = RSMainGame::get()->getNumFont();
	m_iLife = true;
	m_TimeAni =0;
	m_InfoSprite.setDepth(0.1f);
}
void EffectFont::Update(float _Time)
{
	m_TimeAni += _Time ;	
	if (m_TimeAni<= 1)
	{
		m_Y -= _Time*150;
	}
	else
	{
		m_iLife = false;
	}
}
void EffectFont ::Draw(D3DXMATRIX _mtWorld,LPD3DXSPRITE _Handler)
{
	if(m_iLife==true)
	{
		int OffsetSum =0;
		int h = m_Damage;

		while (h/10 > 0)
		{
			OffsetSum+=37;
			h = h/10;
		}
		int Offset =0;
		int t = m_Damage;

		while (t/10 > 0)
		{
			int t2 = t%10;
			m_InfoSprite.setCurFrame(t2);
			m_InfoSprite.setXY(m_X-Offset+ OffsetSum/2,m_Y);
			m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
			t= t/10;
			Offset+=37;
		}
		int t2 = t%10;
		m_InfoSprite.setCurFrame(t2);
		m_InfoSprite.setXY(m_X-Offset+ OffsetSum/2,m_Y);
		m_Sprite->Draw(_mtWorld,m_InfoSprite,_Handler);
	}
}
