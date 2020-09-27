#pragma once
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CEnemyManager.h"
#include "CGame.h"

class CPlayer
{
public:
	CGame* game;
	sf::RectangleShape *rect;
	sf::RectangleShape *bullet;
	sf::Sprite *sprite = new sf::Sprite();

	std::string name = "";
	int lives = 3;
	int score = 0;
	int highestScore = 0;
	int bulletSpeed = 7;
	int bulletsShot = 0;

	static const int wallHeight = 3;
	static const int wallWidth = 5;

	//Can Draw the shape of the barriers using the code below (1 = wall, 0 = gap)
	bool wallShape[wallHeight][wallWidth] = {
		{0,1,1,1,0},
		{1,1,1,1,1},
		{1,1,0,1,1},
	};

	std::vector<sf::RectangleShape*> walls;

	bool canShoot = true;
	bool superBullet = false;
	bool seekingBullet = false;

	CPlayer(sf::RectangleShape *_rect, sf::RectangleShape* _bullet);

	void CreateWalls();

	void MoveRight();
	void MoveLeft();

	void CheckCollision();
	void MoveBullet();

	void RemoveLife();
	void AddLife();
	void AddScore(int _score);

	void ShootSound();
	void KillSound();
};