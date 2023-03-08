#include "board.h"
#include <iostream>

// "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
// "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b ---- - 0 1"

Board::Board(){
}

void Board::loadFEN(std::string fen) {
	//REQUIRES A SPACE AT END OF FEN

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
				this->board[currentIndex] = blackKing;
				currentIndex++;
				break;
			case 'q':
				this->board[currentIndex] = blackQueen;
				currentIndex++;
				break;
			case 'r':
				this->board[currentIndex] = blackRook;
				currentIndex++;
				break;
			case 'b':
				this->board[currentIndex] = blackBishop;
				currentIndex++;
				break;
			case 'n':
				this->board[currentIndex] = blackKnight;
				currentIndex++;
				break;
			case 'p':
				this->board[currentIndex] = blackPawn;
				currentIndex++;
				break;
			case 'K':
				this->board[currentIndex] = whiteKing;
				currentIndex++;
				break;
			case 'Q':
				this->board[currentIndex] = whiteQueen;
				currentIndex++;
				break;
			case 'R':
				this->board[currentIndex] = whiteRook;
				currentIndex++;
				break;
			case 'B':
				this->board[currentIndex] = whiteBishop;
				currentIndex++;
				break;
			case 'N':
				this->board[currentIndex] = whiteKnight;
				std::cout << this->board[currentIndex] << std::endl;
				currentIndex++;
				break;
			case 'P':
				this->board[currentIndex] = whitePawn;
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
	std::string fen = "";
	unsigned int count = 0;
	unsigned int rowtotal = 0;
	for (auto& piecePlacementData : board) {
		if (rowtotal == 8) {
			rowtotal = 0;
			if (count > 0) {
				fen.append(std::to_string(count));
			}
			count = 0;
			fen.append("/");
		}
		if ((piecePlacementData != empty) && (count > 0)){
			fen.append(std::to_string(count));
			count = 0;
		}
		
		switch (piecePlacementData){
			case blackKing:
				rowtotal++;
				fen.append("k");
				break;
			case blackQueen:
				rowtotal++;
				fen.append("q");
				break;
			case blackRook:
				rowtotal++;
				fen.append("r");
				break;
			case blackBishop:
				rowtotal++;
				fen.append("b");
				break;
			case blackKnight:
				rowtotal++;
				fen.append("n");
				break;
			case blackPawn:
				rowtotal++;
				fen.append("p");
				break;
			case whiteKing:
				rowtotal++;
				fen.append("K");
				break;
			case whiteQueen:
				rowtotal++;
				fen.append("Q");
				break;
			case whiteRook:
				rowtotal++;
				fen.append("R");
				break;
			case whiteBishop:
				rowtotal++;
				fen.append("B");
				break;
			case whiteKnight:
				rowtotal++;
				fen.append("N");
				break;
			case whitePawn:
				rowtotal++;
				fen.append("P");
				break;
			case empty:
				if (count == 8) {
					fen.append(std::to_string(count));
					count = 0;
					rowtotal = 0;
				}
				count++;
				rowtotal++;
		}
	}
	std::string fenActiveColour = (activeColour == black) ? "b" : "w";
	fen.append(fenActiveColour);
	//Add castling rights to fen
	//Add lastmove to fen
	//Add halfmove clock
	//Add fullmove number
	return fen;
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
	std::cout << std::endl << enpassant64Index << std::endl << halfmoveClock << std::endl<< fullmoveNumber;
}