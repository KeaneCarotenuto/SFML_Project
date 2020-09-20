#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include"CEnemyManager.h";

class CPlayer
{

public:
	sf::RectangleShape *rect;
	sf::RectangleShape *bullet;

	std::string name = "";
	int lives = 3;
	int score = 0;
	int bulletSpeed;

	bool canShoot = true;

	CPlayer(sf::RectangleShape *_rect, sf::RectangleShape* _bullet);

	void MoveRight();
	void MoveLeft();

	void CheckBulletCollision(CEnemyManager* _eManager);
	void MoveBullet();
};