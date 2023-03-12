#include "piece.h"
#include <SFML/Graphics.hpp>
Piece::Piece(const PieceConstructorArgs& args) :
	sprite{ args.sprite }
{
	sprite.setPosition((args.index % 8) * 60, ((args.index - args.index % 8) / 8) * 60);
}

sf::Sprite Piece::getSprite() {
	return sprite;
}

void Piece::changePosition(unsigned int index) {
	sprite.setPosition((index % 8) * 60, ((index - index % 8) / 8) * 60);
}
