#pragma once
#include <vector>
#include"SFML/Graphics.hpp"

#include"CPlayer.h"

class CGame
{
public:
	std::vector<sf::Drawable*> toDraw;

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

	CPlayer *player;

	sf::Font MyFont;

	int state = 0;
	int menuState = 2;
	bool frozenMenu = false;
	bool frozenEnter = false;

	int volume = 100;
};