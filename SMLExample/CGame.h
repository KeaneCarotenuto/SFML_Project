#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"CEnemyManager.h"
#include"CEnemy.h"
#include"CButton.h"

class CPlayer;

class CGame
{
public:
	//List of items to draw on a frame (cleared after every frame)
	std::vector<sf::Drawable*> toDraw;

	#pragma region Screen Options
	std::vector<sf::Drawable*> MenuDraw;
	enum MenuOptions {
		M_Title,	
		M_Subtitle,
		M_PlayText,
		M_Options,
		M_Credits,
		M_Exit

	};

	std::vector<sf::Drawable*> OptionsDraw;
	enum OptionsOptions {
		O_Title,
		O_Subtitle,
		O_Volume,
		O_Return

	};

	std::vector<sf::Drawable*> CreditsDraw;
	enum CreditsOptions {
		C_Title,
		C_Subtitle,
		C_Cred1,
		C_Cred2,
		C_Return

	};

	std::vector<sf::Drawable*> EndScreenDraw;
	enum EndScreenOptions {
		E_Title,
		E_Subtitle,
		E_HighScore,
		E_Score,
		E_Return

	};

	std::vector<sf::Drawable*> HighscoreDraw;
	enum HighscoreOptions {
		H_Title,
		H_Score,
		H_Subtitle,
		H_HighScores
	};

	std::vector<CButton*> Buttons;
	enum ButtonsOptions {
		B_Title,
		B_AddLife,
		B_AddScore,
		b_SpeedAliens,
		B_SlowAliens,
		B_SuperBullets,
		B_SpawnMysteryShip,
		B_RepairWalls
	};

	std::vector<sf::Drawable*> gameDraw;
	enum GameDrawables {
		G_Lives,
		G_Score

	};
 #pragma endregion

	//Window Pointers
	sf::Window* mainWindow = NULL;
	sf::Window* debugWindow = NULL;
	sf::Window* highscoreWindow = NULL;

	//Player and enemies
	CPlayer *player = nullptr;
	CEnemyManager *enemyManager = nullptr;

	//Pixel Font
	sf::Font MyFont;

	//Game sprites
	sf::Texture topTex;
	sf::Texture middleTex;
	sf::Texture bottomTex;
	sf::Texture mysteryTex;
	
	//Sounds
	sf::SoundBuffer shootBuffer;
	sf::Sound shootSound;

	sf::SoundBuffer killBuffer;
	sf::Sound killSound;

	sf::SoundBuffer explodeBuffer;
	sf::Sound explodeSound;

	std::vector<sf::SoundBuffer*> musicBuffer;
	sf::Sound musicSound;
	int currentMusic = 0;
	sf::Clock musicClock;

	//FixedUpdate() call rate
	float step = (1.0f / 60.0f);

	//Program trackers
	int state = 0;
	int menuState = 2;
	bool frozenMenu = false;
	bool frozenEnter = false;
	bool frozenClick = false;

	int quitTimer = 3500;
	int debugTimer = 2500;

	//Settings
	int volume = 100;
};