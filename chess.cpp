#include "Chess.h"
Chess::Chess(const ChessConstructorArgs& args):
	screenHeight{ args.screenHeight },
	screenWidth{ args.screenWidth },
	texturePath{ args.texturePath }
{
	blackKingImg.loadFromFile(texturePath + "/blackKing.png");
	blackQueenImg.loadFromFile(texturePath + "/blackQueen.png");
	blackRookImg.loadFromFile(texturePath + "/blackRook.png");
	blackBishopImg.loadFromFile(texturePath + "/blackBishop.png");
	blackKnightImg.loadFromFile(texturePath + "/blackKnight.png");
	blackPawnImg.loadFromFile(texturePath + "/blackPawn.png");
	whiteKingImg.loadFromFile(texturePath + "/whiteKing.png");
	whiteQueenImg.loadFromFile(texturePath + "/whiteQueen.png");
	whiteRookImg.loadFromFile(texturePath + "/whiteRook.png");
	whiteBishopImg.loadFromFile(texturePath + "/whiteBishop.png");
	whiteKnightImg.loadFromFile(texturePath + "/whiteKnight.png");
	whitePawnImg.loadFromFile(texturePath + "/whitePawn.png");
	boardImg.loadFromFile(texturePath + "/board.png");

	boardSprite.setTexture(boardImg);

}
void Chess::createWindow() {
	window.create(sf::VideoMode(screenWidth, screenHeight),"Chess-");
}
void Chess::destroyWindow() {
	window.close();
}

void Chess::draw(sf::Sprite sprite) {
	window.draw(sprite);
}

void Chess::update() {
	
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	//window.clear();
	//window.draw(boardSprite);
	//window.display();

}
void Chess::start(Piece piece) {
	//TEST
	window.draw(boardSprite);
	draw(piece.getSprite());
	window.display();
	//ENDTEST
	while (window.isOpen()) {
		update();
	}
	destroyWindow();
}