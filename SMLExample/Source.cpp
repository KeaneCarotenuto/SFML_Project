#include <vector>
#include <string>
#include"SFML/Graphics.hpp"

#include"CGame.h"
#include"CPlayer.h"




void Start();
void Menu();
void Options();
void Credits();

int FixedUpdate();
void Input();

void Draw(sf::RenderWindow& window);


CGame game;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invaders - By Keane Carotenuto");

	// Load from a font file on disk
	if (!game.MyFont.loadFromFile("uni.ttf"))
	{
	}

	Start();

	float step = (1.0f / 60.0f); // Modify this to change physics rate.
	float stepTime = 0;
	bool drawn = false;

	sf::Clock clock;

	while (window.isOpen())
	{
		stepTime += clock.getElapsedTime().asSeconds();
		clock.restart();

		while (stepTime >= step)
		{
			if (FixedUpdate() == 0) return 0;

			stepTime -= step;
			drawn = false;
		}

		if (drawn)
		{
			sf::sleep(sf::seconds(0.01f));
		}
		else
		{
			Draw(window);

			drawn = true;
		}


		sf::Event newEvent;

		while (window.pollEvent(newEvent))
		{
			if (newEvent.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}

	return 0;
}

void Start() {
	
	//Create Player
	sf::RectangleShape* rect = new sf::RectangleShape;
	CPlayer *player =  new CPlayer(rect);
	game.player = player;
	rect->setSize(sf::Vector2f(20.0f, 20.0f));
	rect->setFillColor(sf::Color::Green);
	rect->setPosition(400, 550);
	rect->setRotation(45);

#pragma region "Menu Drawables"
	//Title
	sf::Text *M_title =  new sf::Text;
	M_title->setString("Space Invaders");
	M_title->setCharacterSize(50);
	M_title->setFillColor(sf::Color::White);
	M_title->setStyle(sf::Text::Style::Bold);
	M_title->setPosition(30, 30);
	game.MenuDraw.push_back(M_title);

	//Subtitle
	sf::Text* M_subtitle = new sf::Text;
	M_subtitle->setString("By Keane Carotenuto");
	M_subtitle->setCharacterSize(16);
	M_subtitle->setFillColor(sf::Color::Color(180,180,180,255));
	M_subtitle->setStyle(sf::Text::Style::Italic);
	M_subtitle->setPosition(30, 100);
	game.MenuDraw.push_back(M_subtitle);

	//Play
	sf::Text* M_playText = new sf::Text;
	M_playText->setString("Play");
	M_playText->setCharacterSize(30);
	M_playText->setFillColor(sf::Color::White);
	M_playText->setPosition(30, 150);
	game.MenuDraw.push_back(M_playText);

	//Options
	sf::Text* M_optionsText = new sf::Text;
	M_optionsText->setString("Options");
	M_optionsText->setCharacterSize(30);
	M_optionsText->setFillColor(sf::Color::White);
	M_optionsText->setPosition(30, 200);
	game.MenuDraw.push_back(M_optionsText);

	//Credit
	sf::Text* creditText = new sf::Text;
	creditText->setString("Credits");
	creditText->setCharacterSize(30);
	creditText->setFillColor(sf::Color::White);
	creditText->setPosition(30, 250);
	game.MenuDraw.push_back(creditText);

	//Exit
	sf::Text* M_exitText = new sf::Text;
	M_exitText->setString("Exit");
	M_exitText->setCharacterSize(30);
	M_exitText->setFillColor(sf::Color::White);
	M_exitText->setPosition(30, 300);
	game.MenuDraw.push_back(M_exitText);
#pragma endregion

#pragma region "Options Drawables"
	//Title
	sf::Text* O_title = new sf::Text;
	O_title->setString("Options");
	O_title->setCharacterSize(50);
	O_title->setFillColor(sf::Color::White);
	O_title->setStyle(sf::Text::Style::Bold);
	O_title->setPosition(30, 30);
	game.OptionsDraw.push_back(O_title);

	//Subtitle
	sf::Text* O_subtitle = new sf::Text;
	O_subtitle->setString("Press Enter To Scroll Through Options");
	O_subtitle->setCharacterSize(16);
	O_subtitle->setFillColor(sf::Color::Color(180, 180, 180, 255));
	O_subtitle->setStyle(sf::Text::Style::Italic);
	O_subtitle->setPosition(30, 100);
	game.OptionsDraw.push_back(O_subtitle);

	//Volume
	sf::Text* O_volumeText = new sf::Text;
	O_volumeText->setString("Volume: " + std::to_string(game.volume));
	O_volumeText->setCharacterSize(30);
	O_volumeText->setFillColor(sf::Color::White);
	O_volumeText->setPosition(30, 150);
	game.OptionsDraw.push_back(O_volumeText);

	//Return
	sf::Text* O_returnText = new sf::Text;
	O_returnText->setString("Return");
	O_returnText->setCharacterSize(30);
	O_returnText->setFillColor(sf::Color::White);
	O_returnText->setPosition(30, 200);
	game.OptionsDraw.push_back(O_returnText);
#pragma endregion

#pragma region "Credits Drawables"
	//Title
	sf::Text* C_title = new sf::Text;
	C_title->setString("Credits");
	C_title->setCharacterSize(50);
	C_title->setFillColor(sf::Color::White);
	C_title->setStyle(sf::Text::Style::Bold);
	C_title->setPosition(30, 30);
	game.CreditsDraw.push_back(C_title);

	//Subtitle
	sf::Text* C_subtitle = new sf::Text;
	C_subtitle->setString("Programmed by Keane Carotenuto");
	C_subtitle->setCharacterSize(16);
	C_subtitle->setFillColor(sf::Color::Color(180, 180, 180, 255));
	C_subtitle->setStyle(sf::Text::Style::Italic);
	C_subtitle->setPosition(30, 100);
	game.CreditsDraw.push_back(C_subtitle);

	//Credit1
	sf::Text* C_Cred1 = new sf::Text;
	C_Cred1->setString("Programmer: Keane Carotenuto");
	C_Cred1->setCharacterSize(30);
	C_Cred1->setFillColor(sf::Color::White);
	C_Cred1->setPosition(30, 150);
	game.CreditsDraw.push_back(C_Cred1);

	//Credit1
	sf::Text* C_Cred2 = new sf::Text;
	C_Cred2->setString("Sound: Keane Carotenuto");
	C_Cred2->setCharacterSize(30);
	C_Cred2->setFillColor(sf::Color::White);
	C_Cred2->setPosition(30, 200);
	game.CreditsDraw.push_back(C_Cred2);

	//Return
	sf::Text* C_returnText = new sf::Text;
	C_returnText->setString("Return");
	C_returnText->setCharacterSize(30);
	C_returnText->setFillColor(sf::Color::White);
	C_returnText->setPosition(30, 250);
	game.CreditsDraw.push_back(C_returnText);
#pragma endregion
}

int FixedUpdate() {
	game.toDraw.clear();

	switch (game.state)
	{
	case 0:
		Menu();
		break;

	case 2:
		Options();
		break;

	case 3:
		Credits();
		break;

	case 10:
		game.toDraw.push_back(game.player->rect);
		Input();
		break;

	default:
		return 0;
		break;
	}
	
	return 1;
}

void Menu() {
	//Adds menu items to draw list
	for (sf::Drawable* item : game.MenuDraw)
	{
		game.toDraw.push_back(item);
	}

	//Moving Selection with Keys (frozen menu is used to move only one option at a time)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (game.frozenMenu == false) game.menuState = ((game.menuState > game.M_PlayText) ? game.menuState -1 : game.M_PlayText);
		game.frozenMenu = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (game.frozenMenu == false) game.menuState = ((game.menuState < game.M_Exit) ? game.menuState +1 : game.M_Exit);
		game.frozenMenu = true;
	}
	else {
		game.frozenMenu = false;
	}
	
	//Set All To White, Except Selected, Which is Green
	for (int i = game.M_PlayText; i <= game.M_Exit; i++)
	{
		dynamic_cast<sf::Text&> (*game.MenuDraw[i]).setFillColor(sf::Color::White);
	}
	dynamic_cast<sf::Text&> (*game.MenuDraw[game.menuState]).setFillColor(sf::Color::Green);


	//Checks what option to choose when user 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (!game.frozenEnter) {
			game.frozenEnter = true;
			switch (game.menuState)
			{
			case game.M_PlayText:
				game.state = 10;
				break;

			case game.M_Options:
				game.state = 2;
				break;

			case game.M_Credits:
				game.state = 3;
				break;

			default:
				game.state = -1;
				break;
			}
		}
		
	}
	else {
		game.frozenEnter = false;
	}
}

void Options() {
	//Adds options items to draw list
	for (sf::Drawable* item : game.OptionsDraw)
	{
		game.toDraw.push_back(item);
	}

	//Moving Selection with Keys (frozen menu is used to move only one option at a time)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (game.frozenMenu == false) game.menuState = ((game.menuState > game.O_Volume) ? game.menuState -1 : game.O_Volume);
		game.frozenMenu = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (game.frozenMenu == false) game.menuState = ((game.menuState < game.O_Return) ? game.menuState +1 : game.O_Return);
		game.frozenMenu = true;
	}
	else {
		game.frozenMenu = false;
	}

	//Set All To White, Except Selected, Which is Green
	for (int i = game.O_Volume; i <= game.O_Return; i++)
	{
		dynamic_cast<sf::Text&> (*game.OptionsDraw[i]).setFillColor(sf::Color::White);
	}
	dynamic_cast<sf::Text&> (*game.OptionsDraw[game.menuState]).setFillColor(sf::Color::Green);


	//Checks what option to choose when user 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (!game.frozenEnter) {
			game.frozenEnter = true;
			switch (game.menuState)
			{
			case game.O_Volume:
				(game.volume < 100) ? game.volume += 10 : game.volume = 0;
				dynamic_cast<sf::Text&> (*game.OptionsDraw[game.O_Volume]).setString("Volume: " + std::to_string(game.volume));
				break;

			default:
				game.state = 0;
				break;
			}
		}
	}
	else {
		game.frozenEnter = false;
	}
}

void Credits() {
	//Adds options items to draw list
	for (sf::Drawable* item : game.CreditsDraw)
	{
		game.toDraw.push_back(item);
	}
	
	game.menuState = game.C_Return;

	dynamic_cast<sf::Text&> (*game.CreditsDraw[game.menuState]).setFillColor(sf::Color::Green);

	//Checks what option to choose when user 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (!game.frozenEnter) {
			game.frozenEnter = true;
			switch (game.menuState)
			{

			default:
				game.state = 0;
				break;
			}
		}
	}
	else {
		game.frozenEnter = false;
	}
}


void Input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		game.player->MoveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		game.player->MoveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		
	}
}

void Draw(sf::RenderWindow& window) {
	window.clear();

	for (sf::Drawable* item : game.toDraw)
	{
		if (typeid(*item) == typeid(sf::Text)) {
			dynamic_cast<sf::Text&> (*item).setFont(game.MyFont);
		}

		window.draw((*item));
	}

	//window.draw(*(game.player->rect));

	window.display();
}
