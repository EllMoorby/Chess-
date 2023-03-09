#pragma once
#include <string>
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
	
	sf::Texture blackKing;
	sf::Texture blackQueen;
	sf::Texture blackRook;
	sf::Texture blackBishop;
	sf::Texture blackKnight;
	sf::Texture blackPawn;
	sf::Texture whiteKing;
	sf::Texture whiteQueen;
	sf::Texture whiteRook;
	sf::Texture whiteBishop;
	sf::Texture whiteKnight;
	sf::Texture whitePawn;
	sf::Texture board;

	sf::Sprite boardSprite;

public:
	Chess(const ChessConstructorArgs& args);
	void start();
	void update();
	void createWindow();
	void destroyWindow();
	void movePiece();
	void draw(unsigned int x, unsigned int y, sf::Sprite sprite);
};

