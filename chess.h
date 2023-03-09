#pragma once
#include <string>
#include "board.h"
#include "piece.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct ChessConstructorArgs {
	unsigned int screenHeight;
	unsigned int screenWidth;
	std::string texturePath;
};

class Chess
{
private:
	unsigned int screenHeight;
	unsigned int screenWidth;
	std::string texturePath;
	sf::RenderWindow window;
	sf::Event event;

	/*sf::Texture blackKingImg;
	sf::Texture blackQueenImg;
	sf::Texture blackRookImg;
	sf::Texture blackBishopImg;
	sf::Texture blackKnightImg;
	sf::Texture blackPawnImg;
	sf::Texture whiteKingImg;
	sf::Texture whiteQueenImg;
	sf::Texture whiteRookImg;
	sf::Texture whiteBishopImg;
	sf::Texture whiteKnightImg;
	sf::Texture whitePawnImg;
	sf::Texture boardImg;*/

	sf::Sprite boardSprite;

public:
	Board board; //Can be moved to private with getters and setters
	Chess(const ChessConstructorArgs& args);
	void start(Piece piece);
	void update();
	void createWindow();
	void destroyWindow();
	void movePiece();
	void draw(sf::Sprite sprite);

	//TESTING AREA
	sf::Texture blackKingImg;
	sf::Texture blackQueenImg;
	sf::Texture blackRookImg;
	sf::Texture blackBishopImg;
	sf::Texture blackKnightImg;
	sf::Texture blackPawnImg;
	sf::Texture whiteKingImg;
	sf::Texture whiteQueenImg;
	sf::Texture whiteRookImg;
	sf::Texture whiteBishopImg;
	sf::Texture whiteKnightImg;
	sf::Texture whitePawnImg;
	sf::Texture boardImg;
};

