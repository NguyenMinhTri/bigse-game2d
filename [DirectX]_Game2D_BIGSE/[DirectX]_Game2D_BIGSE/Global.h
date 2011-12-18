#pragma  once
#define  g_SCREEN_WIDTH		 1024
#define  g_SCREEN_HEIGHT	 720
#define  g_CELL				 50
#define  g_VY_JUMP			 300
#define  g_GRAVITY			 400
#define  g_VX				 100

enum STATE 
{
	PLAY,
	MENU,
	ABOUT,
	EXIT
};

enum ID
{
	PLAYER,
};
enum STT 
{
	READY,
	ACTIVE,
	COOLDOWN
};
