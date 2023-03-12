#include "Chess.h"
Chess::Chess(const ChessConstructorArgs& args) :
	screenHeight{ args.screenHeight },
	screenWidth{ args.screenWidth },
	texturePath{ args.texturePath }
{
	board.Board::Board({ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true, texturePath });
	boardImg.loadFromFile(texturePath + "/board.png");
	boardSprite.setTexture(boardImg);

}
void Chess::createWindow() {
	window.create(sf::VideoMode(screenWidth, screenHeight),"Chess-");
}
void Chess::destroyWindow() {
	window.close();
}

void Chess::drawBoard() {
	if (!board.getDrawBoardOnScreenEnabled()) {
		return;
	}
	window.draw(boardSprite);
	for (auto& piece : board.getPieceSprites()) {
		window.draw(piece.getSprite());
	}
}

void Chess::update() {
	
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	window.clear();
	drawBoard();
	window.display();

}
void Chess::start() {
	board.updatePieceSprites();
	while (window.isOpen()) {
		update();
	}
	destroyWindow();
}