#include "CEnemy.h"

CEnemy::CEnemy(float _x, float _y, std::string _str, sf::Color _col)
{
	type = _str;

	trans = new sf::RectangleShape();
	//Create Player
	trans->setSize(sf::Vector2f( (_str == "mystery" ? 46.0f : 20.0f), 20.0f));
	trans->setFillColor(_col);
	trans->setPosition(_x, _y);

	sprite = new sf::Sprite();
}
