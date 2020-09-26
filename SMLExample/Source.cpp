#pragma warning(push)
#pragma warning(disable : 26812)  //cannot change type to enum class as it is within sfml

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <SFML/Graphics.hpp>

#include"CGame.h"
#include"CPlayer.h"
#include"CEnemyManager.h"
#include"CEnemy.h"
#include"CButton.h"

void Start();
void Menu();
void Options();
void Credits();
void Game();
void EndScreen();

int FixedUpdate();
void Input();
void CheckButtonsPressed();

void CreateText(std::string _string, int _fontSize, sf::Color _colour, sf::Text::Style _style, float _x, float _y, std::vector<sf::Drawable*>& vector);
void CreateButton(void(*function)(), std::string _string, int _fontSize, sf::Color _tColour, sf::Text::Style _style, float _x, float _y, sf::Color _bgColour, float _padding);

void Draw(sf::RenderWindow& mainWindow, sf::RenderWindow& debugWindow, sf::RenderWindow& highscoreWindow);

CGame game;
CEnemyManager enemyManager;

void test() {
	std::cout << "Worked";
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invaders - By Keane Carotenuto");

	sf::RenderWindow debugWindow(sf::VideoMode(300, 600), "DEBUG WINDOW");
	debugWindow.setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x, window.getPosition().y));

	sf::RenderWindow highscoreWindow(sf::VideoMode(300, 600), "HIGHSCORES");
	highscoreWindow.setPosition(sf::Vector2i(window.getPosition().x - highscoreWindow.getSize().x, window.getPosition().y));


	game.mainWindow = &window;
	game.debugWindow = &debugWindow;
	game.highscoreWindow = &highscoreWindow;

	debugWindow.setVisible(false);

	window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);

	// Load from a font file on disk
	if (!game.MyFont.loadFromFile("uni.ttf"))
	{
	}

	Start();

	float stepTime = 0;
	bool drawn = false;

	sf::Clock clock;

	while (window.isOpen() == true)
	{
		stepTime += clock.getElapsedTime().asSeconds();
		clock.restart();

		while (stepTime >= game.step)
		{
			if (FixedUpdate() == 0) return 0;

			stepTime -= game.step;
			drawn = false;
		}

		if (drawn)
		{
			//sf::sleep(sf::seconds(0.01f));
		}
		else
		{
			Draw(window, debugWindow, highscoreWindow);

			drawn = true;
		}

		CheckButtonsPressed();


		sf::Event newEvent;

		while (window.pollEvent(newEvent))
		{
			if (newEvent.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		while (debugWindow.pollEvent(newEvent))
		{
			if (newEvent.type == sf::Event::Closed)
			{
				debugWindow.setVisible(false);
			}
		}
	}

	return 0;
}


void AddLife() {
	game.player->AddLife();
}

void AddScore() {
	game.player->AddScore(100);
}

void SlowAliens() {
	game.enemyManager->SlowEnemies();
}

void SpeedAliens() {
	game.enemyManager->SpeedEnemies();
}

void SuperBullets() {
	game.player->superBullet = !game.player->superBullet;
	game.player->bullet->setScale(game.player->superBullet ? 8.0f : 1.0f, game.player->superBullet ? 12.0f : 1.0f);
	game.Buttons[game.B_SuperBullets]->rect->setFillColor( (game.player->superBullet ? sf::Color::Color(0, 180, 0, 255) : sf::Color::White));
}

void SpawnMysteryShip() {
	game.enemyManager->SpawnMystery(std::rand() % 2);
}

void RepairWalls() {
	game.player->CreateWalls();
}


void Start() {
	srand((unsigned)time(NULL));

	game.enemyManager = &enemyManager;

	//Create Player
	game.player = new CPlayer(new sf::RectangleShape, new sf::RectangleShape);
	game.player->rect->setSize(sf::Vector2f(33.0f, 20.0f));
	game.player->rect->setFillColor(sf::Color::Green);
	game.player->rect->setPosition(400, 550);
	game.player->bullet = new sf::RectangleShape;
	game.player->bullet->setSize(sf::Vector2f(5.0f, 20.0f));
	game.player->bullet->setFillColor(sf::Color::White);
	game.player->bullet->setPosition(-100, -100);
	game.player->game = &game;


	enemyManager.CreateAllEnemies();

	for (int i = 0; i < 3; i++) {
		sf::RectangleShape* tempBullet = new sf::RectangleShape;
		tempBullet->setSize(sf::Vector2f(5.0f, 20.0f));
		tempBullet->setFillColor(sf::Color::White);
		tempBullet->setPosition(-100, -200);
		enemyManager.bullets.push_back(tempBullet);
	}


	CreateButton(nullptr, "Debug Buttons", 25, sf::Color::White, sf::Text::Style::Regular, 20, 10, sf::Color::Black, 0);
	CreateButton(&AddLife, "Add Life", 15, sf::Color::Black, sf::Text::Style::Regular, 20, 60, sf::Color::White, 5);
	CreateButton(&AddScore, "Add Score", 15, sf::Color::Black, sf::Text::Style::Regular, 20, 90, sf::Color::White, 5);
	CreateButton(&SlowAliens, "Slow Aliens", 15, sf::Color::Black, sf::Text::Style::Regular, 20, 120, sf::Color::White, 5);
	CreateButton(&SpeedAliens, "Speed Aliens", 15, sf::Color::Black, sf::Text::Style::Regular, 20, 150, sf::Color::White, 5);
	CreateButton(&SuperBullets, "Super Bullets", 15, sf::Color::Black, sf::Text::Style::Regular, 20, 180, sf::Color::White, 5);
	CreateButton(&SpawnMysteryShip, "Spawn Mystery", 15, sf::Color::Black, sf::Text::Style::Regular, 20, 210, sf::Color::White, 5);
	CreateButton(&RepairWalls, "Repair Walls", 15, sf::Color::Black, sf::Text::Style::Regular, 20, 240, sf::Color::White, 5);


#pragma region "Menu Drawables"
	//Title
	CreateText("Space Invaders", 55, sf::Color::White, sf::Text::Style::Bold, 30, 30, game.MenuDraw);
	//Subtitle
	CreateText("By Keane Carotenuto", 16, sf::Color::Color(180, 180, 180, 255), sf::Text::Style::Italic, 30, 100, game.MenuDraw);
	//Play
	CreateText("Play", 30, sf::Color::White, sf::Text::Style::Regular, 30, 150, game.MenuDraw);
	//Options
	CreateText("Options", 30, sf::Color::White, sf::Text::Style::Regular, 30, 200, game.MenuDraw);
	//Credit
	CreateText("Credits", 30, sf::Color::White, sf::Text::Style::Regular, 30, 250, game.MenuDraw);
	//Exit
	CreateText("Exit", 30, sf::Color::White, sf::Text::Style::Regular, 30, 300, game.MenuDraw);
#pragma endregion

#pragma region "Options Drawables"
	//Title
	CreateText("Options", 55, sf::Color::White, sf::Text::Style::Bold, 30, 30, game.OptionsDraw);
	//Subtitle
	CreateText("Press Enter To Scroll Through an Option", 16, sf::Color::Color(180, 180, 180, 255), sf::Text::Style::Italic, 30, 100, game.OptionsDraw);
	//Volume
	CreateText("Volume: " + std::to_string(game.volume), 30, sf::Color::White, sf::Text::Style::Regular, 30, 150, game.OptionsDraw);
	//Return
	CreateText("Return", 30, sf::Color::White, sf::Text::Style::Regular, 30, 200, game.OptionsDraw);

	CreateText("Controls: ", 40, sf::Color::White, sf::Text::Style::Regular, 30, 280, game.OptionsDraw);

	int _y = 340;
	CreateText("Menus: ", 25, sf::Color::White, sf::Text::Style::Regular, (float)400, (float)_y, game.OptionsDraw);
	CreateText("-Up/Down Keys to Move \nSelection", 20, sf::Color::White, sf::Text::Style::Regular, (float)400, (float)_y + 30, game.OptionsDraw);
	CreateText("-Enter to Accept Selection", 20, sf::Color::White, sf::Text::Style::Regular, (float)400, (float)_y + 90, game.OptionsDraw);

	CreateText("Game: ", 25, sf::Color::White, sf::Text::Style::Regular, (float)30, (float)_y, game.OptionsDraw);
	CreateText("-Left/Right Keys to Move \nLeft and Right", 20, sf::Color::White, sf::Text::Style::Regular, (float)30, (float)_y + 30, game.OptionsDraw);
	CreateText("-Space to Shoot", 20, sf::Color::White, sf::Text::Style::Regular, (float)30, (float)_y + 90, game.OptionsDraw);
	CreateText("-Hold Escape to return to Menu", 20, sf::Color::White, sf::Text::Style::Regular, (float)30, (float)_y + 120, game.OptionsDraw);
	CreateText("-Hold Tab to Open to Debug", 20, sf::Color::White, sf::Text::Style::Regular, (float)30, (float)_y + 150, game.OptionsDraw);
#pragma endregion

#pragma region "Credits Drawables"
	//Title
	CreateText("Credits", 50, sf::Color::White, sf::Text::Style::Bold, 30, 30, game.CreditsDraw);
	//Subtitle
	CreateText("KeaneCarotenuto@gmail.com", 16, sf::Color::Color(180, 180, 180, 255), sf::Text::Style::Italic, 30, 100, game.CreditsDraw);
	//Credit1
	CreateText("Programmer: Keane Carotenuto", 30, sf::Color::White, sf::Text::Style::Regular, 30, 150, game.CreditsDraw);
	//Credit2
	CreateText("Sound: Keane Carotenuto", 30, sf::Color::White, sf::Text::Style::Regular, 30, 200, game.CreditsDraw);
	//Return
	CreateText("Return", 30, sf::Color::White, sf::Text::Style::Regular, 30, 250, game.CreditsDraw);
#pragma endregion

#pragma region "End Screen Drawables"
	//Title
	CreateText("Game Over", 50, sf::Color::Red, sf::Text::Style::Bold, 30, 30, game.EndScreenDraw);
	//Subtitle
	CreateText("Invaders took over!", 16, sf::Color::Color(255, 180, 180, 255), sf::Text::Style::Italic, 30, 100, game.EndScreenDraw);
	//Highscore
	CreateText("Highest Score: ", 30, sf::Color::White, sf::Text::Style::Regular, 30, 150, game.EndScreenDraw);
	//Your Score
	CreateText("Your Score: " + std::to_string(game.player->score), 30, sf::Color::White, sf::Text::Style::Bold, 30, 200, game.EndScreenDraw);
	//Return
	CreateText("Return", 30, sf::Color::White, sf::Text::Style::Regular, 30, 280, game.EndScreenDraw);
#pragma endregion

#pragma region "Highscore Drawables"
	//Title
	CreateText("HighScores", 40, sf::Color::White, sf::Text::Style::Bold, 10, 30, game.HighscoreDraw);
	//Subtitle
	CreateText("Your Score: " + std::to_string(game.player->score), 20, sf::Color::White, sf::Text::Style::Bold, 10, 90, game.HighscoreDraw);
	//Credit1
	CreateText("Top 10 Scores:", 18, sf::Color::Color(180, 180, 180, 255), sf::Text::Style::Underlined, 10, 150, game.HighscoreDraw);
	//Credit2
	CreateText("", 20, sf::Color::White, sf::Text::Style::Regular, 10, 180, game.HighscoreDraw);
#pragma endregion

	CreateText("Lives: " + std::to_string(game.player->lives), 20, sf::Color::Green, sf::Text::Style::Bold, 300, 10, game.gameDraw);
	CreateText("Score: " + std::to_string(game.player->score), 20, sf::Color::Green, sf::Text::Style::Bold, 30, 10, game.gameDraw);

	game.player->CreateWalls();
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

	case 4:
		EndScreen();
		break;

	case 10:
		Game();
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

	CheckButtonsPressed();

	//Moving Selection with Keys (frozen menu is used to move only one option at a time)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (game.frozenMenu == false) game.menuState = ((game.menuState > game.M_PlayText) ? game.menuState - 1 : game.M_PlayText);
		game.frozenMenu = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (game.frozenMenu == false) game.menuState = ((game.menuState < game.M_Exit) ? game.menuState + 1 : game.M_Exit);
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
				game.player->score = -1; game.player->AddScore(1);
				game.player->lives = 2; game.player->AddLife();
				game.player->canShoot = true;
				game.player->bullet->setPosition(-100, -100);
				game.player->CreateWalls();
				game.enemyManager->CreateAllEnemies();
				game.enemyManager->speed = 1;
				game.enemyManager->moveDown = false;
				game.enemyManager->atBot = false;
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
		if (game.frozenMenu == false) game.menuState = ((game.menuState > game.O_Volume) ? game.menuState - 1 : game.O_Volume);
		game.frozenMenu = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (game.frozenMenu == false) game.menuState = ((game.menuState < game.O_Return) ? game.menuState + 1 : game.O_Return);
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
			game.state = 0;
		}
	}
	else {
		game.frozenEnter = false;
	}
}

void Game() {
	game.player->CheckBulletCollision(&enemyManager);
	game.player->MoveBullet();
	enemyManager.MoveEnemies();
	enemyManager.MoveBullet();
	

	if (game.enemyManager->atBot) {
		while (game.player->lives > 0) {
			game.player->RemoveLife();
		}
	}

	game.toDraw.push_back(game.player->bullet);

	for (sf::RectangleShape* item : game.player->walls) {
		game.toDraw.push_back(item);
	}

	for (sf::Drawable* item : game.gameDraw) {
		game.toDraw.push_back(item);
	}

	for (sf::RectangleShape* item : enemyManager.bullets) {
		game.toDraw.push_back(item);
	}
	Input();
}

void EndScreen() {

	//Adds options items to draw list
	for (sf::Drawable* item : game.EndScreenDraw)
	{
		if (item == game.EndScreenDraw[game.E_HighScore]) dynamic_cast<sf::Text&> (*game.EndScreenDraw[game.E_HighScore]).setString("Highest Score: " + std::to_string(game.player->highestScore));
		if (item == game.EndScreenDraw[game.E_Score]) dynamic_cast<sf::Text&> (*game.EndScreenDraw[game.E_Score]).setString("Your Score: " + std::to_string(game.player->score));

		game.toDraw.push_back(item);
	}

	game.menuState = game.E_Return;

	dynamic_cast<sf::Text&> (*game.EndScreenDraw[game.menuState]).setFillColor(sf::Color::Green);

	//Checks what option to choose when user 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (!game.frozenEnter) {
			game.frozenEnter = true;
			game.state = 0;
			game.menuState = game.M_PlayText;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && game.player->canShoot)
	{
		game.player->canShoot = false;
		game.player->bullet->setPosition(game.player->rect->getPosition().x + game.player->rect->getLocalBounds().width/2 - 2.5f, game.player->rect->getPosition().y - 20);
		game.player->bulletsShot++;

		if (game.player->bulletsShot == 23 || (game.player->bulletsShot > 23 && (game.player->bulletsShot - 23) % 15 == 0)) {
			game.enemyManager->SpawnMystery(std::rand() % 2);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		CreateText("Hold Escape for  " + std::to_string(game.quitTimer / 1000) + "s  To Quit", 20, sf::Color::White, sf::Text::Style::Regular, 10, 570, game.toDraw);
		game.quitTimer -= (int)((game.step) * 1000);

		if (game.quitTimer < 0) game.state = 0;
	}
	else {
		game.quitTimer = 3500;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		CreateText("Hold Tab for  " + std::to_string(game.debugTimer / 1000) + "s  To Open Debug", 20, sf::Color::White, sf::Text::Style::Regular, 10, 570, game.toDraw);
		game.debugTimer -= (int)((game.step) * 1000);

		if (game.debugTimer < 0) {
			game.debugWindow->setVisible(true);
		}
	}
	else {
		game.debugTimer = 2500;
	}
}

void CheckButtonsPressed() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!game.frozenClick) {
			float mX = (float)sf::Mouse::getPosition(*game.debugWindow).x;
			float mY = (float)sf::Mouse::getPosition(*game.debugWindow).y;
			for (CButton* _button : game.Buttons)
			{
				float bX = _button->rect->getPosition().x;
				float bY = _button->rect->getPosition().y;
				float bW = _button->rect->getSize().x;
				float bH = _button->rect->getSize().y;

				if (mX >= bX && mY >= bY && mX <= (bX + bW) && mY < (bY + bH)) {
					if (_button->function != nullptr) _button->function();
				}
			}
		}
		game.frozenClick = true;
	}
	else {
		game.frozenClick = false;
	}
}

void CreateText(std::string _string = "Temp", int _fontSize = 20, sf::Color _colour = sf::Color::White, sf::Text::Style _style = sf::Text::Style::Regular, float _x = 100, float _y = 100, std::vector<sf::Drawable*>& vector = game.toDraw) {
	sf::Text* tempText = new sf::Text;
	tempText->setString(_string);
	tempText->setCharacterSize(_fontSize);
	tempText->setFillColor(_colour);
	tempText->setStyle(_style);
	tempText->setPosition(_x, _y);
	vector.push_back(tempText);
}

//std::string _string, int _fontSize, sf::Color _tColour, sf::Text::Style _style, float _x , float _y, sf::Color _bgColour, float _padding
void CreateButton(void(*function)(), std::string _string = "Temp", int _fontSize = 20, sf::Color _tColour = sf::Color::White, sf::Text::Style _style = sf::Text::Style::Regular, float _x = 100, float _y = 100, sf::Color _bgColour = sf::Color::Black, float _padding = 10) {
	sf::Text* tempText = new sf::Text;
	tempText->setString(_string);
	tempText->setCharacterSize(_fontSize);
	tempText->setFillColor(_tColour);
	tempText->setStyle(_style);
	tempText->setPosition(_x, _y);
	tempText->setFont(game.MyFont);

	sf::RectangleShape* buttonRect = new sf::RectangleShape;
	buttonRect->setPosition(tempText->getGlobalBounds().left - _padding, tempText->getGlobalBounds().top - _padding);
	buttonRect->setSize(sf::Vector2f(tempText->getGlobalBounds().width + (2 * _padding), tempText->getGlobalBounds().height + (2 * _padding)));
	buttonRect->setFillColor(_bgColour);

	CButton* button = new CButton(buttonRect, tempText, function);
	game.Buttons.push_back(button);
}

void Draw(sf::RenderWindow& mainWindow, sf::RenderWindow& debugWindow, sf::RenderWindow& highscoreWindow) {
	mainWindow.clear();

	for (sf::Drawable* item : game.toDraw)
	{
		if (typeid(*item) == typeid(sf::Text)) {
			dynamic_cast<sf::Text&> (*item).setFont(game.MyFont);
		}

		mainWindow.draw((*item));
	}


	//I know that this is a stupid way to do it... I added sprites at the end, and you need to load the texture before you use draw it in the given scope.. So I had to do this...
	if (game.state == 10) {

		sf::Texture ptexture;

		if (!ptexture.loadFromFile("player.png", sf::IntRect(0, 0, 33, 20)))
		{
			std::cout << "FAIL";
		}

		game.player->sprite->setTexture(ptexture);
		game.player->sprite->setPosition(game.player->rect->getPosition());
		mainWindow.draw(*(game.player->sprite));



		for (CEnemy* enemy : enemyManager.enemies) {
			sf::Texture texture;

			if (enemy->type == "top") {
				if (!texture.loadFromFile("top.png", sf::IntRect(0, 0, 20, 20)))
				{
					std::cout << "FAIL";
				}
			}
			else if (enemy->type == "middle") {
				if (!texture.loadFromFile("middle.png", sf::IntRect(0, 0, 20, 20)))
				{
					std::cout << "FAIL";
				}
			}
			else if (enemy->type == "bottom") {
				if (!texture.loadFromFile("bottom.png", sf::IntRect(0, 0, 20, 20)))
				{
					std::cout << "FAIL";
				}
			}
			else if (enemy->type == "mystery") {
				if (!texture.loadFromFile("mystery.png", sf::IntRect(0, 0, 46, 20)))
				{
					std::cout << "FAIL";
				}
			}
			enemy->sprite->setTexture(texture);
			enemy->sprite->setPosition(enemy->trans->getPosition());

			mainWindow.draw(*(enemy->sprite));
		}
	}

	mainWindow.display();


	if (debugWindow.isOpen()) {
		debugWindow.clear();

		for (CButton* item : game.Buttons)
		{

			debugWindow.draw((*item->rect));

			sf::Text* _text = item->text;

			if (typeid(*_text) == typeid(sf::Text)) {
				dynamic_cast<sf::Text&> (*_text).setFont(game.MyFont);

				debugWindow.draw((*_text));
			}
		}

		debugWindow.display();
	}

	if (highscoreWindow.isOpen()) {

		highscoreWindow.clear();

		std::string line = "";
		std::string finalLine;
		std::ifstream myfile("HIGHSCORES.txt");
		if (myfile.is_open())
		{
			int count = 0;
			while (std::getline(myfile, line) && count < 10)
			{
				if (count == 0) game.player->highestScore = std::stoi(line);
				count++;
				finalLine += line + "\n";
			}

			
			myfile.close();
		}
		else std::cout << "Unable to open file 1\n";

		dynamic_cast<sf::Text&> (*game.HighscoreDraw[game.H_HighScores]).setString(finalLine);
		dynamic_cast<sf::Text&> (*game.HighscoreDraw[game.H_Score]).setString("Your Score: " + std::to_string(game.player->score));

		for (sf::Drawable* item : game.HighscoreDraw)
		{

			if (typeid(*item) == typeid(sf::Text)) {
				dynamic_cast<sf::Text&> (*item).setFont(game.MyFont);
			}

			highscoreWindow.draw((*item));
		}

		highscoreWindow.display();
	}



	if(mainWindow.getSize() != sf::Vector2u(800, 600)) mainWindow.setSize(sf::Vector2u(800, 600));
	if (debugWindow.getSize() != sf::Vector2u(300, 600)) debugWindow.setSize(sf::Vector2u(300, 600));
	if (highscoreWindow.getSize() != sf::Vector2u(300, 600)) highscoreWindow.setSize(sf::Vector2u(300, 600));
	if (debugWindow.getPosition() != sf::Vector2i(mainWindow.getPosition().x + mainWindow.getSize().x, mainWindow.getPosition().y)) debugWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x + mainWindow.getSize().x, mainWindow.getPosition().y));
	if (highscoreWindow.getPosition() != sf::Vector2i(mainWindow.getPosition().x - highscoreWindow.getSize().x, mainWindow.getPosition().y)) highscoreWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x - highscoreWindow.getSize().x, mainWindow.getPosition().y));
	
}