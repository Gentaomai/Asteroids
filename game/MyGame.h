#pragma once


class CMyGame : public CGame
{
public:
	// Game variables
	int score;
	int level;
	int lives;
	bool gamewon;

	// Define sprites and other instance variables here
	CSprite player;	// Player spaceship
	CSprite startScreen; 
	CSprite background;
	CSprite Health;
	CSprite enemyship;
	CSprite powerup;
	CSprite extralife;
	CSprite doublelife;

	CSpriteList shotList;  // sprite list of shots
	CSpriteList asteroidList;  // sprite list of asteroids
	CSpriteList enemyshipList; // sprite list of enemy ships
	CSpriteList explosionList; // sprite list of explosions
	CSpriteList powerupList;
	CSpriteList extralifeList; // sprite list of extra lives
	CSoundPlayer explosion; //explosion sound 
	CSoundPlayer shotsound;  //shot sound

	
	// -----    your new member functions ------
	void SetupLevel1();
	void SetupLevel2();

	void PlayerControl();
	void AsteroidControl();
	void EnemyspaceshipControl();
	void ShotControl();
	void PowerUpControl();
	void ExtralifeControl();
	void DoublelifeControl();


public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
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
