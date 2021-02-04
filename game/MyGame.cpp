#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void)
{
	score = 0;
	level = 1;
	lives = 3;
	gamewon=false;

}


CMyGame::~CMyGame(void)
 {
// TODO: add destruction code here
 }

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	if (IsMenuMode() || IsGameOver()) return;

	long t = GetTime();

// update sprites here
	player.Update(t);
	Health.Update(t);
	enemyship.Update(t);
	powerup.Update(t);
	extralife.Update(t);
	doublelife.Update(t);

// todo: update sprite lists
	for (CSprite* shot : shotList) shot->Update(t);
	for (CSprite* asteroid : asteroidList) asteroid->Update(t);
	for (CSprite* explosion : explosionList) explosion->Update(t); 
	for (CSprite* powerup : powerupList) 
	{ 
		powerup->Update(t);
	}
	for (CSprite* extralife : extralifeList) extralife->Update(t);
	for (CSprite* doublelife : extralifeList) doublelife->Update(t);
	for (CSprite* enemyship : enemyshipList)
	{
		enemyship->Update(t);
	}
// ---- game rules -----

// todo: game rule to win the game

	if (player.GetHealth() == 0) GameOver();

// delete a shot if outside of the screen area

// remove deleted sprites from list
	shotList.delete_if(deleted);
	asteroidList.delete_if(deleted);
	explosionList.delete_if(deleted);
	enemyshipList.delete_if(deleted);
	powerupList.delete_if(deleted);
	extralifeList.delete_if(deleted);

// player control function
	PlayerControl();
// asteroid control function
	AsteroidControl();
// enemyspaceship control function
	EnemyspaceshipControl();
	{
		if (score == 10);
	{
		enemyship.LoadImage("enemyspaceship.bmp", CColor::Black());
		enemyship.SetImage("enemyspaceship.bmp");
		enemyship.SetPosition(0, 10);
	}


		for (CSprite* enemyship : enemyshipList)
			{
				enemyship->Update(t);



			}
	}	
//shot control function
	ShotControl();
//increase laser shooting speed (shot)
	PowerUpControl();
//extralife to give the player 1 extra life
	ExtralifeControl();
//give the player 2 lives instead of 1
	DoublelifeControl();

}
	

void CMyGame::PlayerControl()
{
	if (IsKeyDown(SDLK_w)) player.SetSpeed(player.GetSpeed() + 0.90);

	// drag
	player.SetSpeed(player.GetSpeed() - 0.6f);
	if (player.GetSpeed() < 0) player.SetSpeed(0);

// wrap-around effect - screen size 800x600

	if (player.GetX() < 0) player.SetX(800);
	if (player.GetX() > 800) player.SetX(0);
	if (player.GetY() < 0) player.SetY(600);
	if (player.GetY() > 600) player.SetY(0);
//Call asteroid list for hit test condition
	for (CSprite* asteroid : asteroidList)
	{
		if (player.HitTest(asteroid))
		{
//player and asteroid collision - resets player position. Deletes the asteroid that was touched and takes one life.
			player.SetHealth(player.GetHealth() - 1);
			asteroid->Delete();
			player.SetPosition(400, 300);
			player.SetSpeed(0);
			player.SetDirection(0);
			player.SetRotation(0);

		}
	}
}

void CMyGame::AsteroidControl()
{
	for (CSprite* asteroid : asteroidList)
// todo: wrap-around effect for asteroids

	{
		if (asteroid->GetX() < 0) asteroid->SetX(800);
		if (asteroid->GetX() > 800) asteroid->SetX(0);
		if (asteroid->GetY() < 0) asteroid->SetY(600);
		if (asteroid->GetY() > 600) asteroid->SetY(0);
	}

//small asteroids respawn
	if (score <= 250)
	{
		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 0, "asteroid1.bmp", CColor::Black(), GetTime());  //bot left
			newSprite->SetDirection(360.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 0, "asteroid1.bmp", CColor::Black(), GetTime());  //bot right
			newSprite->SetDirection(270.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 600, "asteroid1.bmp", CColor::Black(), GetTime());  //Top left
			newSprite->SetDirection(90.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 600, "asteroid1.bmp", CColor::Black(), GetTime());  //Top right
			newSprite->SetDirection(180.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}
	}

//Big asteroids respawn
	if (score > 250)
	{
		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 0, "asteroid2.bmp", CColor::Black(), GetTime());  //bot left
			newSprite->SetDirection(360.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 0, "asteroid2.bmp", CColor::Black(), GetTime());  //bot right
			newSprite->SetDirection(270.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 600, "asteroid2.bmp", CColor::Black(), GetTime());  //Top left
			newSprite->SetDirection(90.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 600, "asteroid2.bmp", CColor::Black(), GetTime());  //Top right
			newSprite->SetDirection(180.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}
		
//Small asteroids
		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 0, "asteroid1.bmp", CColor::Black(), GetTime());  //bot left
			newSprite->SetDirection(0.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 0, "asteroid1.bmp", CColor::Black(), GetTime());  //bot right
			newSprite->SetDirection(270.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 600, "asteroid1.bmp", CColor::Black(), GetTime());  //Top left
			newSprite->SetDirection(90.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 600, "asteroid1.bmp", CColor::Black(), GetTime());  //Top right
			newSprite->SetDirection(180.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

	}
	if (score > 500)
	{
		//big asteroids respawn
		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 0, "asteroid2.bmp", CColor::Black(), GetTime());  //bot left
			newSprite->SetDirection(0.0f + float(rand() % 90));
			newSprite->SetSpeed(60);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 0, "asteroid2.bmp", CColor::Black(), GetTime());  //bot right
			newSprite->SetDirection(270.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 600, "asteroid2.bmp", CColor::Black(), GetTime());  //Top left
			newSprite->SetDirection(90.0f + float(rand() % 90));
			newSprite->SetSpeed(60);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 600, "asteroid1.bmp", CColor::Black(), GetTime());  //Top right
			newSprite->SetDirection(180.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 0, "asteroid3.bmp", CColor::Black(), GetTime());  //bot left
			newSprite->SetDirection(0.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 0, "asteroid3.bmp", CColor::Black(), GetTime());  //bot right
			newSprite->SetDirection(270.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(0, 600, "asteroid3.bmp", CColor::Black(), GetTime());  //Top left
			newSprite->SetDirection(90.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}

		if (rand() % 250 == 0)
		{
			CSprite* newSprite = new CSprite(800, 600, "asteroid3.bmp", CColor::Black(), GetTime());  //Top right
			newSprite->SetDirection(180.0f + float(rand() % 90));
			newSprite->SetSpeed(50);
			asteroidList.push_back(newSprite);
		}
	}
}

void CMyGame::ShotControl()
{
	//Shots delete when off screen
	for (CSprite* shot : shotList)
	{
		if (shot->GetY() < 0 || shot->GetY() > 600 || shot->GetX() < 0 || shot->GetX() > 800) shot->Delete();
	}

	for (CSprite* shot : shotList)
	{
		// delete a shot if outside of the screen area
		for (CSprite* asteroid : asteroidList)
		{
			if (asteroid->HitTest(shot))
			{
				// delete star
				CSprite* explosion = new CSprite(asteroid->GetX(), asteroid->GetY(), 0, 0, GetTime());
				explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black());
				explosion->SetAnimation("explode", 25);
				explosion->Die(500);
				explosionList.push_back(explosion);
				//add ten to score for every shot which hits the  asteroid
				score = score + 10;
				asteroid->Delete();
				shot->Delete();
				
			}
		}
	}
}

void CMyGame::PowerUpControl()
{
	for (CSprite* powerup : powerupList);
	{
		if (score == 250);
		{
			if (rand() % 60 == 0)
			{
				powerup.LoadImage("powerup.bmp", CColor::Black());
				powerup.SetImage("powerup.bmp");
				powerup.SetPosition(float(rand() % 800), 600);
				powerup.SetSpeed(45);
				powerup.SetDirection(180);
			}
		}
	}
	
}

void CMyGame::ExtralifeControl()
{
}

void CMyGame::DoublelifeControl()
{
}

void CMyGame::EnemyspaceshipControl() 
{
			for (CSprite* enemyspaceship : enemyshipList)
	{
				if (score == 10)
		{

				//Took out CSprite * NewSprite Newsprite instead of enemyship
				CSprite* enemyship = new CSprite(400, 600, "enemyspaceship.bmp", CColor::Black(), GetTime());  //bot left
				enemyshipList.push_back(enemyship);
		}
	}
}
void CMyGame::OnDraw(CGraphics* g) 
{	// TODO: add drawing code here

		if (IsMenuMode())
		{
			startScreen.Draw(g);
			return;
		}

		// todo: draw sprite lists
		background.Draw(g);
		for (CSprite* shot : shotList) shot->Draw(g);
		for (CSprite* asteroid : asteroidList) asteroid->Draw(g);	
		
		
	if (score == 10) 
	{
		for (CSprite* enemyship : enemyshipList) 
				
			{
				enemyship->Draw(g);
			}
	
	}			

		// draw player sprite

		{
			// print score
			player.Draw(g);
			*g << font(28) << color(CColor::Red()) << xy(10, 570) << score;
			// print players lives
			*g << font(28) << color(CColor::Green()) << xy(10, 550) << player.GetHealth();
		}

		if (IsGameOverMode())
		{
			if (gamewon)
			{
				*g << font(46) << color(CColor::Green()) << vcenter << center << " GAME WON ";
			}
			else
			{
				*g << font(46) << color(CColor::Red()) << vcenter << center << " GAME OVER ";
			}
		}
}
	
	// print game over at at the centre of the screen or game won
/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize() 
{
	
	background.SetPosition(400, 300);

	background.LoadImage("background.bmp", CColor::Black());
	background.SetImage("background.bmp");

	player.LoadImage("spaceship.bmp", CColor::Black());
	player.SetImage("spaceship.bmp");

	startScreen.LoadImage("StartScreen.bmp", CColor::Black());
	startScreen.SetImage("StartScreen.bmp");
	startScreen.SetPosition(400, 300);

}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen-
void CMyGame::OnDisplayMenu()
{
	// default level
	level = 1;
	
}


void CMyGame::SetupLevel1()
{
	
	
}


void CMyGame::SetupLevel2()
{
	// todo: Set UFO into position and motion
	
	{
		level == 2;
		SetupLevel2();
	}

}


// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	score = 0;

	gamewon = false;

	// clear lists
	shotList.delete_all();
	asteroidList.delete_all();
	enemyshipList.delete_all();
	powerupList.delete_all();

	if (score == 10) 
	
	{
		enemyship.SetPosition(float(rand() % 800), 600);
		//enemyship.SetMotion(Player.GetX(), Player.GetY());

	}




	player.SetPosition(400, 300);
	player.SetSpeed(0);
	player.SetDirection(0);
	player.SetRotation(0);
	player.SetHealth(3);

	if (level == 1) SetupLevel1();
	if (level == 2) SetupLevel2();

}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}


/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (!IsMenuMode() && sym == SDLK_F2)
		NewGame();

	// --- dealing with menu selections when in Menu Mode
	if (IsMenuMode())
	{
		if (sym == SDLK_1)
		{
			level = 1;
			StartGame();
		}
		else if (sym == SDLK_2)
		{
			level = 2;
			StartGame();
		}
	}
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	player.SetDirection(x - player.GetX(), y - player.GetY());
	player.SetRotation(player.GetDirection() - 0);
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	CSprite*newShot = new CSprite(player.GetX(), player.GetY(), "shot.bmp", CColor::Black(), GetTime());
	newShot->SetDirection(player.GetDirection());
	newShot->SetSpeed(150 + player.GetSpeed());
	newShot->SetRotation(player.GetRotation());
	shotList.push_back(newShot);
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
	CSprite* newShot = new CSprite(player.GetX(), player.GetY(), "shot.bmp", CColor::Black(), GetTime());
	newShot->SetDirection(player.GetDirection());
	newShot->SetSpeed(150 + player.GetSpeed());
	newShot->SetRotation(player.GetRotation());
	shotList.push_back(newShot);

}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
