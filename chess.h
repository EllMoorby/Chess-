#pragma once
#include <string>
#include "test.h"
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
	Pieces pieceOnMouse;
	unsigned int screenHeight;
	unsigned int screenWidth;
	std::string texturePath;
	sf::RenderWindow window;
	sf::Event event;
	Board board;
	sf::Texture boardImg;
	sf::Sprite boardSprite;

public:
	Chess(const ChessConstructorArgs& args);
	void start();
	void update();
	void createWindow();
	void destroyWindow();
	void pickUpPiece();
	void drawBoard();
	unsigned int findIndexFromOnScreenPosition();
	void deleteAtIndexFromPosition();
	void dropPiece();
};

