#include "Chess.h"
Chess::Chess(const ChessConstructorArgs& args):
	screenHeight{ args.screenHeight },
	screenWidth{ args.screenWidth },
	texturePath{ args.texturePath }
{
	blackKing.loadFromFile(texturePath + "/blackKing.png");
	blackQueen.loadFromFile(texturePath + "/blackQueen.png");
	blackRook.loadFromFile(texturePath + "/blackRook.png");
	blackBishop.loadFromFile(texturePath + "/blackBishop.png");
	blackKnight.loadFromFile(texturePath + "/blackKnight.png");
	blackPawn.loadFromFile(texturePath + "/blackPawn.png");
	whiteKing.loadFromFile(texturePath + "/whiteKing.png");
	whiteQueen.loadFromFile(texturePath + "/whiteQueen.png");
	whiteRook.loadFromFile(texturePath + "/whiteRook.png");
	whiteBishop.loadFromFile(texturePath + "/whiteBishop.png");
	whiteKnight.loadFromFile(texturePath + "/whiteKnight.png");
	whitePawn.loadFromFile(texturePath + "/whitePawn.png");
	board.loadFromFile(texturePath + "/board.png");

	boardSprite.setTexture(board);
}
void Chess::createWindow() {
	window.create(sf::VideoMode(screenWidth, screenHeight),"Chess-");
}
void Chess::destroyWindow() {
	window.close();
}

void Chess::update() {
	
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	window.clear();
	window.draw(boardSprite);
	window.display();

}
void Chess::start() {
	while (window.isOpen()) {
		update();
	}
	destroyWindow();
}