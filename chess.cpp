#include "Chess.h"
Chess::Chess(const ChessConstructorArgs& args) :
	screenHeight{ args.screenHeight },
	screenWidth{ args.screenWidth },
	texturePath{ args.texturePath },
	fen{ args.fen }
{
	createWindow();
	board.Board::Board({ fen, true, pieceToTextureDictionary});
	boardImg.loadFromFile(texturePath + "/board.png");
	boardSprite.setTexture(boardImg);
	pieceOnMouse = empty;

}

void Chess::initialiseTextures(std::string texturePath) {
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

	pieceToTextureDictionary[blackKing] = blackKingImg;
	pieceToTextureDictionary[blackQueen] = blackQueenImg;
	pieceToTextureDictionary[blackRook] = blackRookImg;
	pieceToTextureDictionary[blackBishop] = blackBishopImg;
	pieceToTextureDictionary[blackKnight] = blackKnightImg;
	pieceToTextureDictionary[blackPawn] = blackPawnImg;
	pieceToTextureDictionary[whiteKing] = whiteKingImg;
	pieceToTextureDictionary[whiteQueen] = whiteQueenImg;
	pieceToTextureDictionary[whiteRook] = whiteRookImg;
	pieceToTextureDictionary[whiteBishop] = whiteBishopImg;
	pieceToTextureDictionary[whiteKnight] = whiteKnightImg;
	pieceToTextureDictionary[whitePawn] = whitePawnImg;
}

void Chess::createWindow() {
	window.create(sf::VideoMode(screenWidth, screenHeight),"Chess-", sf::Style::Titlebar | sf::Style::Close);
	initialiseTextures(texturePath);
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
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code){
			case sf::Keyboard::Delete:
				deleteAtIndexFromPosition();
				break;
			case sf::Keyboard::R:
				board.loadFEN(fen);
				break;
			}
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button) {
			case sf::Mouse::Left:
				pickUpPiece();
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button) {
			case sf::Mouse::Left:
				dropPiece();
				break;
			}
		}
	}
	
	window.clear();
	board.updatePieceSprites();
	drawBoard();
	if (pieceOnMouse != empty) {
		sf::Sprite tempSprite;
		tempSprite.setTexture(pieceToTextureDictionary[pieceOnMouse]);
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		tempSprite.setPosition(mousePosition.x - 30, mousePosition.y - 30);
		window.draw(tempSprite);
	}
	
	window.display();

}

void Chess::start() {
	board.updatePieceSprites();
	while (window.isOpen()) {
		update();
	}
	destroyWindow();
}

unsigned int Chess::findIndexFromOnScreenPosition() {
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	int x = pos.x;
	int y = pos.y;
	if (x < 0 || y < 0) {
		return 999;
	}

	x /= 60;
	y /= 60;

	if (x > 7 || y > 7) {
		return 999;
	}
	unsigned int index = x + 8 * y;
	return index;
}

void Chess::deleteAtIndexFromPosition() {
	unsigned int index = findIndexFromOnScreenPosition();
	if (index == 999) {
		return;
	}
	board.deleteAtIndex(findIndexFromOnScreenPosition());
}

void Chess::pickUpPiece() {
	if (pieceOnMouse != empty) {
		return;
	}
	unsigned int index = findIndexFromOnScreenPosition();
	if (index == 999) {
		return;
	}
	legalMoves = board.generatePsuedoLegalMoves();
	pieceOnMouse = board.pieceAtIndex(index);
	indexMovedFrom = index;
	board.deleteAtIndex(index);
}

void Chess::dropPiece() {
	if (pieceOnMouse == empty) {
		return;
	}
	unsigned int index = findIndexFromOnScreenPosition();
	if (index == 999) {
		return;
	}
	for (auto& move : legalMoves) {
		if (move.startIndex64 == indexMovedFrom && move.finishIndex64 == index) {
			board.addPieceToIndex(index, pieceOnMouse);
			//TODO
			if (pieceOnMouse == blackKing && indexMovedFrom != index) {
				board.castlingAvailability.blackKingSide = false;
				board.castlingAvailability.blackQueenSide = false;
			}
			else if (pieceOnMouse == whiteKing && indexMovedFrom != index) {
				board.castlingAvailability.whiteKingSide = false;
				board.castlingAvailability.whiteQueenSide = false;
			}
			if (pieceOnMouse == blackRook && indexMovedFrom != index) {
				if (indexMovedFrom == (board.algebraicNotationTo64Index("a8"))) {
					board.castlingAvailability.blackQueenSide = false;
				}
				else if (indexMovedFrom == (board.algebraicNotationTo64Index("h8"))) {
					board.castlingAvailability.blackKingSide = false;
				}
			} else if (pieceOnMouse == whiteRook && indexMovedFrom != index) {
				if (indexMovedFrom == (board.algebraicNotationTo64Index("a1"))) {
					board.castlingAvailability.whiteQueenSide = false;
				}
				else if (indexMovedFrom == (board.algebraicNotationTo64Index("h1"))) {
					board.castlingAvailability.whiteKingSide = false;
				}
			}
			
			if (move.castlingRookMove.castlingRookStartIndex64 != 99 || move.castlingRookMove.castlingRookFinishIndex64 != 99) {
				//Add new rook
				board.addPieceToIndex(move.castlingRookMove.castlingRookFinishIndex64, board.pieceAtIndex(move.castlingRookMove.castlingRookStartIndex64));
				board.deleteAtIndex(move.castlingRookMove.castlingRookStartIndex64);
				*move.castlingRookMove.castlingRight = false;
			}
			
			pieceOnMouse = empty;
			return;
		}
	}
	board.addPieceToIndex(indexMovedFrom, pieceOnMouse);
	pieceOnMouse = empty;
	
}
