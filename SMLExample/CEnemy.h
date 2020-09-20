#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class CEnemy
{
public:
	std::string type;
	sf::RectangleShape* trans;

	CEnemy(float _x, float _y,std::string _str, sf::Color _col);
};

