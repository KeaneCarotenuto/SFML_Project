#include "CPlayer.h"

CPlayer::CPlayer(sf::RectangleShape* _rect, sf::RectangleShape* _bullet) :
	rect(_rect), bullet(_bullet)
{
}

void CPlayer::MoveRight()
{
	if (rect->getPosition().x <= 700) rect->move(3.0f, 0.0f);
}

void CPlayer::MoveLeft()
{
	if (rect->getPosition().x >= 100) rect->move(-3.0f, 0.0f);
}

void CPlayer::CheckBulletCollision(CEnemyManager* _eManager)
{
	if (bullet != nullptr) {

		if (bullet->getPosition().y < 0) {
			canShoot = true;
			bullet->setPosition(-100, -100);
		}

		for (CEnemy* _enemy : _eManager->enemies) {
			if (_enemy->trans->getGlobalBounds().intersects(bullet->getGlobalBounds())) {
				std::vector<CEnemy*>::iterator pos = std::find(_eManager->enemies.begin(), _eManager->enemies.end(), _enemy);

				if (pos != _eManager->enemies.end()) _eManager->enemies.erase(pos);

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
