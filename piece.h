#pragma once
#include <SFML/Graphics.hpp>
#include "test.h"

struct PieceConstructorArgs {
	unsigned int index;
	sf::Sprite sprite;
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

