#pragma once
#include <SFML/Graphics.hpp>
#include "boardData.h"

struct PieceConstructorArgs {
	unsigned int index;
	sf::Sprite sprite;
};

class Piece
{
private:
	sf::Sprite sprite;
	Pieces pieceType;

public:
	Piece(const PieceConstructorArgs& args);
	bool getColour();
	void getPosition(); //EDIT THIS LATER
	void changePosition(unsigned int index);
	sf::Sprite getSprite();
};

