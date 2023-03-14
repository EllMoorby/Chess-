#pragma once
#include "boardData.h"
#include "board.h"
#include "piece.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


struct ChessConstructorArgs {
	unsigned int screenHeight;
	unsigned int screenWidth;
	std::string texturePath;
	std::string fen;
};

class Chess
{
private:
	unsigned int indexMovedFrom;
	std::string fen;
	std::map<Pieces, sf::Texture> pieceToTextureDictionary;
	Pieces pieceOnMouse;
	unsigned int screenHeight;
	unsigned int screenWidth;
	std::string texturePath;
	sf::RenderWindow window;
	sf::Event event;
	Board board;
	sf::Texture boardImg;
	sf::Sprite boardSprite;
	std::vector<Move> legalMoves;

public:
	Chess(const ChessConstructorArgs& args);
	void initialiseTextures(std::string texturePath);
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

