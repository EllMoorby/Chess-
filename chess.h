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
	Board board;
	sf::Texture boardImg;
	sf::Sprite boardSprite;

public:
	//Can be moved to private with getters and setters
	Chess(const ChessConstructorArgs& args);
	void start(Piece piece);
	void update();
	void createWindow();
	void destroyWindow();
	void movePiece();
	void drawBoard();

};

