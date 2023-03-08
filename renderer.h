#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct RendererConstructorArgs {
	unsigned int screenHeight;
	unsigned int screenWidth;
	std::string texturePath;
};

class Renderer
{
private:
	unsigned int screenHeight;
	unsigned int screenWidth;
	std::string texturePath;
	sf::Window window;
	
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

public:
	Renderer(const RendererConstructorArgs& args);
	void createWindow();
	void destroyWindow();
	void draw(unsigned int x, unsigned int y, sf::Sprite sprite);

};

