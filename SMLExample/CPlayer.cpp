#include "CPlayer.h"

CPlayer::CPlayer(sf::RectangleShape* _rect, sf::RectangleShape* _bullet) :
	rect(_rect), bullet(_bullet), game(nullptr)
{
}

void CPlayer::CreateWalls()
{
	//Clear all walls first
	for (sf::RectangleShape* wall : walls) {
		delete wall;
	}
	walls.clear();

	//Create walls
	for (int i = 0; i < 4; i++) {
		for (int y = 0; y < wallHeight; y++) {
			for (int x = 0; x < wallWidth; x++) {
				if (wallShape[y][x]) {
					for (int r = 0; r < 5; r++) { //How many wall pieces per segment (width)
						for (int c = 0; c < 5; c++) { //How many wall pieces per segment (height)
							sf::RectangleShape* tempWall = new sf::RectangleShape;
							tempWall->setSize(sf::Vector2f(3.0f, 3.0f)); //Size of wall piece
							tempWall->setFillColor(sf::Color::Green);
							tempWall->setPosition((float)(100 + (i * 175) + (x * 15) + (r * 3)), (float)( 470 + (y * 15) + (c * 3)));
							walls.push_back(tempWall);
						}
					}
				}
			}
		}
	}
}

void CPlayer::MoveRight()
{
	if (rect->getPosition().x <= 760) rect->move(3.0f, 0.0f);
}

void CPlayer::MoveLeft()
{
	if (rect->getPosition().x >= 20) rect->move(-3.0f, 0.0f);
}

float Distance(int x1, int y1, int x2, int y2)
{
	return sqrt((float)(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0));
}

//The main collosion check for the game.
void CPlayer::CheckCollision()
{
	//Player bullet collosion
	if (bullet != nullptr) {

		if (bullet->getPosition().y < 0) {
			canShoot = true;
			bullet->setPosition(-100, -100);
		}

		//Walls
		for (sf::RectangleShape* wall : walls) {
			//Player bullet with walls
			if (wall->getGlobalBounds().intersects(bullet->getGlobalBounds())) {

				std::vector<sf::RectangleShape*> toDel;

				//Manages the size of explosion and chance of wall being destroyed, gives random explosions
				for (sf::RectangleShape* _2ndwall : walls) {

					float distance = Distance((int)wall->getPosition().x, (int)wall->getPosition().y, (int)_2ndwall->getPosition().x, (int)_2ndwall->getPosition().y);

					float rand = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);

					if (distance < std::rand() % 15 + 3) {
						toDel.push_back(_2ndwall);
					}
				}

				for (sf::RectangleShape* _wall : toDel) {
					std::vector<sf::RectangleShape*>::iterator pos = std::find(walls.begin(), walls.end(), _wall);
					if (pos != walls.end()) walls.erase(pos);

					delete _wall;
				}

				canShoot = true;
				bullet->setPosition(-100, -100);
				break;
			}

			//Enemy bullets with walls
			for (sf::RectangleShape* _bullet : game->enemyManager->bullets) {
				if (wall->getGlobalBounds().intersects(_bullet->getGlobalBounds())) {

					std::vector<sf::RectangleShape*> toDel;

					for (sf::RectangleShape* _2ndwall : walls) {

						float distance = Distance((int)wall->getPosition().x, (int)wall->getPosition().y, (int)_2ndwall->getPosition().x, (int)_2ndwall->getPosition().y);

						if (distance < std::rand() % 15 + 3) {
							toDel.push_back(_2ndwall);
						}
					}

					for (sf::RectangleShape* _wall : toDel) {
						std::vector<sf::RectangleShape*>::iterator pos = std::find(walls.begin(), walls.end(), _wall);
						if (pos != walls.end()) {
							walls.erase(pos);
							delete _wall;
						}
					}

					_bullet->setPosition(-100, -200);
					break;
				}
			}
		}
		

		std::vector<CEnemy*> toDel;

		//Player Bullets and enemies
		for (CEnemy* _enemy : game->enemyManager->enemies) {
			if (_enemy == nullptr) {
				continue;
			}
			sf::FloatRect erect = _enemy->trans->getGlobalBounds();
			sf::FloatRect brect = bullet->getGlobalBounds();

			if (erect.intersects(brect)) {

				KillSound();

				if (_enemy->type == "top") {
					AddScore(30);
				}
				else if (_enemy->type == "middle") {
					AddScore(20);
				}
				else if (_enemy->type == "bottom") {
					AddScore(10);
				}
				else if (_enemy->type == "mystery") {
					AddScore(300);
				}

				game->enemyManager->speed = (abs(game->enemyManager->speed) / (game->enemyManager->speed)) * (abs(game->enemyManager->speed) + 0.01f) ;

				toDel.push_back(_enemy);

				if (!superBullet) {
					canShoot = true;
					bullet->setPosition(-100, -100);
				}
			}
		}

		for (CEnemy* _enemy : toDel) {
			std::vector<CEnemy*>::iterator pos = std::find(game->enemyManager->enemies.begin(), game->enemyManager->enemies.end(), _enemy);
			if (true) {
				game->enemyManager->enemies.erase(pos);
				delete _enemy;
			}
		}
	}

	//Enemy bullets and walls
	for (sf::RectangleShape* _bullet : game->enemyManager->bullets) {
		if (_bullet != nullptr) {
			if (rect->getGlobalBounds().intersects(_bullet->getGlobalBounds())) {
				RemoveLife();
				_bullet->setPosition(-100,-200);
				rect->setPosition(390,rect->getPosition().y);
				break;
				
			}
		}
	}
}

//Moves player bullets
void CPlayer::MoveBullet()
{
	float speed = (superBullet ? -30 : (float)-bulletSpeed);

	if (seekingBullet) { // not used, but cool idea!
		//game->enemyManager->enemies
	}

	if (!canShoot) {
		bullet->move(0, speed);
	}
}

//Manages removing a life from the player and updating it
void CPlayer::RemoveLife()
{
	game->player->lives -= 1;
	dynamic_cast<sf::Text&> (*game->gameDraw[game->G_Lives]).setString("Lives: " + std::to_string(game->player->lives));

	game->explodeSound.setBuffer(game->explodeBuffer);
	game->explodeSound.play();

	if (lives == 0) {
		game->state = 4;

		std::string line;
		std::vector<std::string> lines;
		std::ifstream myfile("HIGHSCORES.txt");
		if (myfile.is_open())
		{
			while (std::getline(myfile, line))
			{
				lines.push_back(line);
			}
			myfile.close();
		}
		else std::cout << "Unable to open file 1\n";

		bool wasInserted = false;
		std::vector<std::string>::iterator it;
		for (it = lines.begin(); it < lines.end(); it++) {
			if (score >= std::stoi(*it)) {
				lines.insert(it, std::to_string((score)));
				wasInserted = true;
				break;
			}
		}
		if (!wasInserted) {
			lines.push_back(std::to_string((score)));
		}


		std::ofstream highscores;
		highscores.open("HIGHSCORES.txt");
		if (highscores.is_open())
		{
			for (it = lines.begin(); it < lines.end(); it++) {
				highscores << *it << "\n";
			}
		}
		else std::cout << "Unable to open file 2\n";
		highscores.close();
	}
}

//same, but for adding!
void CPlayer::AddLife()
{
	game->player->lives += 1;
	dynamic_cast<sf::Text&> (*game->gameDraw[game->G_Lives]).setString("Lives: " + std::to_string(game->player->lives));
}

//Debug option
void CPlayer::AddScore(int _score)
{
	game->player->score += _score;
	dynamic_cast<sf::Text&> (*game->gameDraw[game->G_Score]).setString("Score: " + std::to_string(game->player->score));
}

//Sounds
void CPlayer::ShootSound() {
	game->shootSound.setBuffer(game->shootBuffer);
	game->shootSound.play();
}

void CPlayer::KillSound()
{
	game->killSound.setBuffer(game->killBuffer);
	game->killSound.play();
}
