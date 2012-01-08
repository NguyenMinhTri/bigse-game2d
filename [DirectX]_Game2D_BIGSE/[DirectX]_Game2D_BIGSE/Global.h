#pragma  once
#define  g_SCREEN_WIDTH		 1024
#define  g_SCREEN_HEIGHT	 720
#define  g_CELL				 50
#define  g_VY_JUMP			 300
#define  g_GRAVITY			 400
#define  g_VX				 100
#define  g_GodLike_Beast     50

enum STATE 
{
	PLAY,
	MENU,
	LOADING,
	ABOUT,
	EXIT,
	WorldMap,
	ChoosePlayer,
	MAINMENU,
	SETTING
};

enum ID
{
	PLAYER,

};
enum STT 
{
	READY,
	ACTIVE,
	COOLDOWN,
	TIME,
	FREEZETIME,
	GODLIKE_SKILL1,
	GODLIKE_SKILL2,
	GODLIKE_SKILL3,
	GODLIKE_SKILL4
};
enum P_STT
{
	P_HIDE,
	P_MOVE,
	P_GO,
	P_BACK,
	p_ACTIVE,
	P_DIE 
};