#include "CPlayer.h"

CPlayer::CPlayer(sf::RectangleShape* _rect, sf::RectangleShape* _bullet) :
	rect(_rect), bullet(_bullet)
{
}

void CPlayer::CreateWalls()
{
	walls.clear();

	for (int i = 0; i < 4; i++) {
		for (int y = 0; y < wallHeight; y++) {
			for (int x = 0; x < wallWidth; x++) {
				if (wallShape[y][x]) {

					for (int r = 0; r < 3; r++) {
						for (int c = 0; c < 3; c++) {
							sf::RectangleShape* tempWall = new sf::RectangleShape;
							tempWall->setSize(sf::Vector2f(5.0f, 5.0f));
							tempWall->setFillColor(sf::Color::Green);
							tempWall->setPosition(100 + (i * 175) + (x * 15) + (r * 5), 470 + (y * 15) + (c * 5));

							walls.push_back(tempWall);
							//game->gameDraw.push_back(tempWall);
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
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void CPlayer::CheckBulletCollision(CEnemyManager* _eManager)
{
	if (bullet != nullptr) {

		if (bullet->getPosition().y < 0) {
			canShoot = true;
			bullet->setPosition(-100, -100);
		}

		for (sf::RectangleShape* wall : walls) {
			if (wall->getGlobalBounds().intersects(bullet->getGlobalBounds())) {
				
				std::vector<sf::RectangleShape*> toDel;

				for (sf::RectangleShape* _2ndwall : walls) {

					float distance = Distance(wall->getPosition().x, wall->getPosition().y, _2ndwall->getPosition().x, _2ndwall->getPosition().y);

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
			}
		}

		for (CEnemy* _enemy : _eManager->enemies) {
			if (_enemy->trans->getGlobalBounds().intersects(bullet->getGlobalBounds())) {
				std::vector<CEnemy*>::iterator pos = std::find(_eManager->enemies.begin(), _eManager->enemies.end(), _enemy);

				if (pos != _eManager->enemies.end()) _eManager->enemies.erase(pos);

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

				delete _enemy;

				canShoot = true;
				bullet->setPosition(-100, -100);
			}
		}
	}
}

void CPlayer::MoveBullet()
{
	if (!canShoot) bullet->move(0, -5);
}

void CPlayer::RemoveLife()
{
	game->player->lives -= 1;
	dynamic_cast<sf::Text&> (*game->gameDraw[game->G_Lives]).setString("Lives: " + std::to_string(game->player->lives));
}

void CPlayer::AddLife()
{
	game->player->lives += 1;
	dynamic_cast<sf::Text&> (*game->gameDraw[game->G_Lives]).setString("Lives: " + std::to_string(game->player->lives));
}

void CPlayer::AddScore(int _score)
{
	game->player->score += _score;
	dynamic_cast<sf::Text&> (*game->gameDraw[game->G_Score]).setString("Score: " + std::to_string(game->player->score));
}