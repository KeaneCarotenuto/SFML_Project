#include "CEnemyManager.h"

//Defaults: 5, 11, 100, 100, 500, 200
void CEnemyManager::CreateAllEnemies(int _rows, int _cols, float _startX, float _startY, float _width, float _height)
{
	//Delete all before creation
	for (CEnemy* e : enemies)
	{
		delete e;
	}
	enemies.clear();
	
	//reset speed
	speed = abs(speed);

	//Create Aliens
	for (int row = 0; row < _rows; row++) {
		for (int col = 0; col < _cols; col++) {
			AddEnemy((int)(_startX + (col * (_width/_cols))), (int)(_startY + (row * (_height/_rows))), (row == 0 ? "top" : (row <= 2 ? "middle" : "bottom")), sf::Color::Red);
		}
	}
}

void CEnemyManager::AddEnemy(int _x, int _y, std::string _type, sf::Color _colour)
{
	enemies.push_back( new CEnemy((float)_x, (float)_y, _type, _colour));
}

void CEnemyManager::SpawnMystery(bool left)
{
	CEnemy* e = new CEnemy((float)(left ? -10 : 810), 40, "mystery", sf::Color::Red);
	enemies.push_back(e);
	e->left = left;
}

//Manages the movement of all aliens
void CEnemyManager::MoveEnemies()
{
	//Spawns new round if all are dead
	if (enemies.empty()) {
		CreateAllEnemies();
		speed -= 0.4f;
	}

	moveDown = false;

	for (CEnemy* item : enemies) {
		if (item->trans->getPosition().y >= 550) {
			atBot = true;
			//Reached Player
		}

		if (item->type == "mystery") continue;
		if ((item->trans->getPosition().x < 20 && speed < 0) || (item->trans->getPosition().x > (780 - 20) && speed > 0)) {
			speed *= -1;
			moveDown = true;
		}
	}

	//Movement of Aliens
	for (CEnemy* item : enemies) {
		if (item->type == "mystery") {
			item->trans->move((float)(item->left ? 2 : -2), 0);

			if (item->trans->getPosition().x > 850 || item->trans->getPosition().x < -70) {
				std::vector<CEnemy*>::iterator pos = std::find(enemies.begin(), enemies.end(), item);
				if (pos != enemies.end() ) {
					enemies.erase(pos);
					delete item;
				}
			}
		}
		else {
			item->trans->move(speed, (moveDown ? 20.0f : 0.0f));
		}
		
	}
}

void CEnemyManager::SlowEnemies(float _amount)
{
	speed *= _amount;
}

void CEnemyManager::SpeedEnemies(float _amount)
{
	speed /= _amount;
}

//Manages how aliens shoot
void CEnemyManager::MoveBullet()
{
	for (sf::RectangleShape* _bullet : bullets) {
		if (_bullet->getPosition().x == -100 && _bullet->getPosition().y == -200 && eClock.getElapsedTime().asSeconds() > (1.0f/std::abs(speed))) {
			eClock.restart();

			int tries = 0;
			int rand;
			float x;
			float y;

			//Makes sure mystery ship does not shoot
			do
			{
				tries++;
				rand = std::rand() % enemies.size();
				x = enemies[rand]->trans->getPosition().x + 7.5f;
				y = enemies[rand]->trans->getPosition().y + 20;
			} while (enemies[rand]->type == "mystery" && tries < 100);


			if(tries < 100) _bullet->setPosition(x,y);
			break;
		}
		else {
			if (_bullet->getPosition().x != -100 && _bullet->getPosition().y != -200) _bullet->move(0, 5);
		}

		if (_bullet->getPosition().y > 600) {
			_bullet->setPosition(-100, -200);
		}
	}
}