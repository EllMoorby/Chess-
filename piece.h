#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"

struct PieceConstructorArgs {
	unsigned int index;
	Pieces pieceType;
	sf::Texture texture;
};

class Piece
{
private:
	unsigned int index;
	sf::Sprite sprite;
	Pieces pieceType;

public:
	Piece(const PieceConstructorArgs& args);
	bool getColour();
	void getPosition(); //EDIT THIS LATER
	sf::Sprite getSprite();
};

