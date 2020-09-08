#include "CPlayer.h"

CPlayer::CPlayer(sf::RectangleShape *_rect):
	rect(_rect)
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
