#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include"CEnemy.h"

#include <SFML/Graphics.hpp>

class CEnemyManager
{
public:
	std::vector<CEnemy*> enemies;
	std::vector<sf::RectangleShape*> bullets;
	float speed = 1;
	bool moveDown = false;
	bool atBot = false;
	sf::Clock eClock;

	void CreateAllEnemies(int _rows = 5, int _cols = 11, float _startX = 20, float _startY = 50, float _width = 500, float _height = 200);
	void AddEnemy(int _x, int _y, std::string _type, sf::Color _colour);
	void SpawnMystery(bool left);
	void MoveEnemies();

	void SlowEnemies(float _amount = 0.5f);
	void SpeedEnemies(float _amount = 0.5f);
	void MoveBullet();

};