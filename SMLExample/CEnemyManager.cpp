#include "CEnemyManager.h"

//5, 11, 100, 100, 500, 200
void CEnemyManager::CreateAllEnemies(int _rows, int _cols, float _startX, float _startY, float _width, float _height)
{
	for (int row = 0; row < _rows; row++) {
		for (int col = 0; col < _cols; col++) {
			AddEnemy(_startX + (col * (_width/_cols)), _startY + (row * (_height/_rows)), "basic", sf::Color::Red);
		}
	}
}

void CEnemyManager::AddEnemy(int _x, int _y, std::string _type, sf::Color _colour)
{
	enemies.push_back( new CEnemy(_x, _y, _type, _colour));
}

void CEnemyManager::MoveEnemies()
{
	moveDown = false;

	for (CEnemy* item : enemies) {
		if ((item->trans->getPosition().x < 20 && speed < 0) || (item->trans->getPosition().x > (780 - 20) && speed > 0)) {
			speed *= -1;
			moveDown = true;
		}
	}

	for (CEnemy* item : enemies) {
		item->trans->move(speed, (moveDown ? 20.0f : 0.0f));
	}
}
