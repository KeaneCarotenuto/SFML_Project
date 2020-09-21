#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include"CEnemyManager.h";
#include"CGame.h";

class CPlayer
{
public:
	CGame* game;
	sf::RectangleShape *rect;
	sf::RectangleShape *bullet;

	std::string name = "";
	int lives = 3;
	int score = 0;
	int bulletSpeed;

	static const int wallHeight = 3;
	static const int wallWidth = 5;

	bool wallShape[wallHeight][5] = {
		{0,1,1,1,0},
		{1,1,1,1,1},
		{1,1,0,1,1},
	};

	std::vector<sf::RectangleShape*> walls;

	bool canShoot = true;

	CPlayer(sf::RectangleShape *_rect, sf::RectangleShape* _bullet);

	void CreateWalls();

	void MoveRight();
	void MoveLeft();

	void CheckBulletCollision(CEnemyManager* _eManager);
	void MoveBullet();

	void RemoveLife();
	void AddLife();
	void AddScore(int _score);
};