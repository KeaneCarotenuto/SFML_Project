#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class CPlayer
{

public:
	sf::RectangleShape *rect;

	CPlayer(sf::RectangleShape *_rect);

	void MoveRight();
	void MoveLeft();
};

