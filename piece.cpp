#include "piece.h"

Piece::Piece(const PieceConstructorArgs& args):
	index{args.index},
	pieceType{args.pieceType},
	texture{args.texture}
{
	xPos = (index % 8)*60;
	yPos = (index / 8)*60;
	sprite.setTexture(texture);
}

sf::Sprite Piece::getSprite() {
	return sprite;
}
