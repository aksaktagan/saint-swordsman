#pragma once

class CMyGame : public CGame
{
	// Define sprites and other instance variables here
	CSprite player;	// player sprite
	CSprite samurai;
	CSprite samuraiAttack1;
	CSprite samuraiAttack2;
	CSprite samuraiPreAttack1;
	CSprite samuraiAttack5;
	CSprite slash;
	CSprite tree;
	CSprite treeAttack;
	CSprite energyBall;
	CSprite skeleton;
	CSprite spider;
	CSprite magician;
	CSprite swing;
	CSprite hitbox;
	CSprite rootAttack;
	CSprite rootAttackEnds;
	CSprite startScreen;
    CSprite background;
	CSprite doorToLvl2;
	CSprite openingDoor2;
	CSprite doorToLvl3;
	CSprite caveLine;
	CSprite hellLine1;
	CSprite hellLine;
	CSprite hpPotion;
	CSprite strengthPotion;
	CSprite tower1;
	CSprite tower2;
	CSprite textbox;
	CSprite text1;
	CSprite text2;
	CSprite chest;
	CSprite pressE;

	CSoundPlayer bmusic;
	CSoundPlayer swinging;
	CSoundPlayer zorotheme;
	CSoundPlayer zoroonigiri;
	CSoundPlayer zoroattack1;
	CSoundPlayer zoroattack2;
	CSoundPlayer zoroattack3;
	CSoundPlayer explosion;
	CSoundPlayer victory;
	CSoundPlayer gameover;

	CSpriteList firstSwingList;
	CSpriteList secondSwingList;
	CSpriteList mobDeathList;
	CSpriteList skeletonspawnList;
	CSpriteList skeletonAttackList;
	CSpriteList spiderspawnList;
	CSpriteList spiderAttackList;
	CSpriteList magicList;
	CSpriteList skeletonSwingList;

	int level;

	int score;

	int swingcounter = 0;
	int spawncounter = 0;
	int attackcounter = 0;
	int damagecounter = 0;
	int animationcounter = 0;
	int energyballcounter = 0;

	int lives = 3;

	int whatlvl = 0;

	int rootdamage = 1;
	int damage = 10;
	int treehealth = 1000;

	int magicianhealth = 2000;

	int zorohealth = 500;

	int playerdamage1 = 10;
	int playerdamage2 = 1;
	int playerhealth = 100;

	int tower1health = 200;
	int tower2health = 200;
	
	bool isDamaged = false;
	bool magicianIsDead = false;

	bool isZoroTpAttack = false;
	bool isZoroFirstAttack = false;
	bool isZoroSecondAttack = false;

	bool isPressed1TimeZoro = false;
	bool isPressed2ndTimeZoro = false;

	bool gamewon = false;

	// my own member functions
void PlayerControl();
void BossControl();
void EnemyControl();
void SpawnControl();
void DeathControl();

void SetupLevel1();
void SetupLevel2();
void SetupLevel3();

void isFirstLvl();
void isSecondLvl();


public:
	CMyGame(void);
	~CMyGame(void);

	enum animation_state { NONE, STANDLEFT, STANDRIGHT, WALKLEFT, WALKRIGHT, FIRSTATTACKR, FIRSTATTACKL, SECONDATTACKR, SECONDATTACKL, BLOCK, DEATH };

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);
	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
