#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class CEnemy
{
public:
	std::string type;
	sf::RectangleShape* trans;
	sf::Sprite* sprite;

	bool left;

	CEnemy(float _x, float _y,std::string _str, sf::Color _col);
};

