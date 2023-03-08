#include "board.h"
#include <iostream>

// "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
// "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b ---- - 0 1"

Board::Board(){
}

void Board::loadFEN(std::string fen) {
	fen.append(" ");

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
	unsigned int rowTotal = 0;
	for (auto& piecePlacementData : board) {
		if (rowTotal == 8) {
			rowTotal = 0;
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
				rowTotal++;
				fen.append("k");
				break;
			case blackQueen:
				rowTotal++;
				fen.append("q");
				break;
			case blackRook:
				rowTotal++;
				fen.append("r");
				break;
			case blackBishop:
				rowTotal++;
				fen.append("b");
				break;
			case blackKnight:
				rowTotal++;
				fen.append("n");
				break;
			case blackPawn:
				rowTotal++;
				fen.append("p");
				break;
			case whiteKing:
				rowTotal++;
				fen.append("K");
				break;
			case whiteQueen:
				rowTotal++;
				fen.append("Q");
				break;
			case whiteRook:
				rowTotal++;
				fen.append("R");
				break;
			case whiteBishop:
				rowTotal++;
				fen.append("B");
				break;
			case whiteKnight:
				rowTotal++;
				fen.append("N");
				break;
			case whitePawn:
				rowTotal++;
				fen.append("P");
				break;
			case empty:
				if (count == 8) {
					fen.append(std::to_string(count));
					count = 0;
					rowTotal = 0;
				}
				count++;
				rowTotal++;
		}
	}
	fen.append(" ");
	std::string fenActiveColour = (activeColour == black) ? "b" : "w";
	fen.append(fenActiveColour);
	fen.append(" ");
	//Add castling rights to fen
	fen.append((castlingAvailability.whiteKingSide == true) ? "K" : "-");
	fen.append((castlingAvailability.whiteQueenSide == true) ? "Q" : "-");
	fen.append((castlingAvailability.blackKingSide == true) ? "k" : "-");
	fen.append((castlingAvailability.blackQueenSide == true) ? "q" : "-");
	fen.append(" ");
	//Add lastmove to fen
	unsigned int index = enpassant64Index;
	unsigned int units = 8-(index / 8);
	char tens = char(index-units+87);
	std::string output = "";
	output.push_back(tens);
	output.append(std::to_string(units));

	fen.append(output);
	fen.append(" ");
		//Add halfmove clock
	fen.append(std::to_string(halfmoveClock));
	fen.append(" ");
	//Add fullmove number
	fen.append(std::to_string(fullmoveNumber));
	return fen;
}

unsigned int Board::algebraicNotationTo64Index(std::string square) {
	unsigned int file = square[0];
	unsigned int rank = square[1];
	return ((file - 97) + (8 * (56 - rank)));
}

void Board::displayBoard() {
	unsigned int count = 0;
	for (auto& piecePlacementData : board) {
		count++;
		std::cout << piecePlacementData;
		if (count == 8) {
			std::cout << std::endl;
			count = 0;
		}
			
	}
}