#include "piece.h"
#include <SFML/Graphics.hpp>
Piece::Piece(const PieceConstructorArgs& args) :
	index{ args.index },
	sprite{ args.sprite }
{
	sprite.setPosition((index % 8) * 60, ((index - index % 8) / 8) * 60);
}

sf::Sprite Piece::getSprite() {
	return sprite;
}
