#include "board.h"
#include <iostream>

// "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
// "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b ---- - 0 1"

Board::Board(){
}

void Board::loadFEN(std::string fen) {

	Pieces board[64] = {
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty
	};

	std::string fenFields[6]; //fenBoard, fenActiveColour, fenCastlingAvailability, fenEnpassantSquare, fenHalfmoveClock, fenFullmoveNumber

	int start = 0;
	int end = fen.find(" ");
	int currentField = 0;
	while (end != -1) {
		fenFields[currentField] = fen.substr(start, end - start);
		start = end + 1;
		end = fen.find(" ",start);
		currentField++;
	}

	unsigned int currentIndex = 0;
	for (auto& piecePlacementData : fenFields[0]) {
		switch (piecePlacementData) {
			case '/':
				currentIndex++;
				break;
			case '1':
				currentIndex += 1;
				break;
			case '2':
				currentIndex += 2;
				break;
			case '3':
				currentIndex += 3;
				break;
			case '4':
				currentIndex += 4;
				break;
			case '5':
				currentIndex += 5;
				break;
			case '6':
				currentIndex += 6;
				break;
			case '7':
				currentIndex += 7;
				break;
			case '8':
				currentIndex += 8;
				break;
			case 'k':
				board[currentIndex] = blackKing;
				currentIndex++;
				break;
			case 'q':
				board[currentIndex] = blackQueen;
				currentIndex++;
				break;
			case 'r':
				board[currentIndex] = blackRook;
				currentIndex++;
				break;
			case 'b':
				board[currentIndex] = blackBishop;
				currentIndex++;
				break;
			case 'n':
				board[currentIndex] = blackKnight;
				currentIndex++;
				break;
			case 'p':
				board[currentIndex] = blackPawn;
				currentIndex++;
				break;
			case 'K':
				board[currentIndex] = whiteKing;
				currentIndex++;
				break;
			case 'Q':
				board[currentIndex] = whiteQueen;
				currentIndex++;
				break;
			case 'R':
				board[currentIndex] = whiteRook;
				currentIndex++;
				break;
			case 'B':
				board[currentIndex] = whiteBishop;
				currentIndex++;
				break;
			case 'N':
				board[currentIndex] = whiteKnight;
				currentIndex++;
				break;
			case 'P':
				board[currentIndex] = whitePawn;
				currentIndex++;
				break;


		}
	}

	activeColour = (fenFields[1] == "w")? white : black;
	castlingAvailability.whiteKingSide = (fenFields[2][0] != '-') ? true : false;
	castlingAvailability.whiteQueenSide = (fenFields[2][1] != '-') ? true : false;
	castlingAvailability.blackKingSide = (fenFields[2][2] != '-') ? true : false;
	castlingAvailability.blackQueenSide = (fenFields[2][3] != '-') ? true : false;

	enpassant64Index = algebraicNotationTo64Index(fenFields[3]);

	halfmoveClock = std::stoi(fenFields[4]);
	fullmoveNumber = std::stoi(fenFields[5]);


}

std::string Board::getBoardAsFEN() {
	return "a";
}

unsigned int Board::algebraicNotationTo64Index(std::string square) {
	unsigned int file = square[0];
	unsigned int rank = square[1];
	return ((file - 97) + (8 * (56 - rank)));
}

void Board::displayBoard() {
	for (auto& piecePlacementData : board) {
		std::cout << piecePlacementData;

	}
}