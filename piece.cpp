#include "piece.h"

Piece::Piece(const PieceConstructorArgs& args):
	index{args.index},
	pieceType{args.pieceType}
{
	int xPos = (index % 8)*60;
	int yPos = (index / 8)*60;
	sprite.setTexture(args.texture);
	sprite.setPosition(xPos, yPos);
}

sf::Sprite Piece::getSprite() {
	return sprite;
}
