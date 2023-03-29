#include "board.h"
#include <iostream>

Board::Board() {

}

Board::Board(const BoardConstructorArgs args) :
	drawBoardOnScreenEnabled{ args.drawBoardOnScreenEnabled },
	pieceToTextureDictionary{ args.pieceToTextureDictionary }
{
	loadFEN(args.fen);
}



void Board::loadFEN(std::string fen) {
	fen.append(" "); // Space Added for Final FEN Split

	board = {
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty,
		empty, empty, empty, empty, empty, empty, empty, empty
	};
	
	//Board, ActiveColour, CastlingAvailability, EnpassantSquare, HalfmoveClock, FullmoveNumber
	std::string fenFields[6]; 

	//Splits FEN String into Fields by Splitting on a Space
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
	std::string fen = "";
	
	//Add Piece Placement Data to FEN
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
	
	//Add Active Colour to FEN
	std::string fenActiveColour = (activeColour == black) ? "b" : "w";
	fen.append(fenActiveColour);
	fen.append(" ");
	
	//Add Castling Rights to FEN
	fen.append((castlingAvailability.whiteKingSide == true) ? "K" : "-");
	fen.append((castlingAvailability.whiteQueenSide == true) ? "Q" : "-");
	fen.append((castlingAvailability.blackKingSide == true) ? "k" : "-");
	fen.append((castlingAvailability.blackQueenSide == true) ? "q" : "-");
	fen.append(" ");
	
	//Add Last Pawn Move to FEN
	unsigned int index = enpassant64Index;
	unsigned int units = 8-(index / 8);
	char tens = char(index-units+87);
	std::string output = "";
	output.push_back(tens);
	output.append(std::to_string(units));

	fen.append(output);
	fen.append(" ");
	
	//Add Halfmove Clock
	fen.append(std::to_string(halfmoveClock));
	fen.append(" ");
	
	//Add Fullmove Number
	fen.append(std::to_string(fullmoveNumber));
	return fen;
}

unsigned int Board::algebraicNotationTo64Index(std::string square) {
	unsigned int file = square[0];
	unsigned int rank = square[1];
	return ((file - 97) + (8 * (56 - rank)));
}

bool Board::getDrawBoardOnScreenEnabled() {
	return drawBoardOnScreenEnabled;
}

void Board::updatePieceSprites(){
	pieceSprites.clear();
	unsigned int index{ 0 };
	for (auto& square : board) {
		if (square != empty) {
			sf::Sprite pieceSprite;
			pieceSprite.setTexture(pieceToTextureDictionary[square]);
			pieceSprites.push_back(Piece({ index, pieceSprite }));
		}
		index++;
	}
}
std::vector<Piece> Board::getPieceSprites() {
	return pieceSprites;
}

void Board::displayBoard() {
	if (!drawBoardOnScreenEnabled) {
		return;
	}
	updatePieceSprites();
}

void Board::deleteAtIndex(unsigned int index) {
	board[index] = empty;
}

Pieces Board::pieceAtIndex(unsigned int index) {
	return board[index];
}

void Board::addPieceToIndex(unsigned int index, Pieces piece) {
	board[index] = piece;
}

std::vector<Move> Board::generatePsuedoLegalMoves() {
	// For Sliding Pieces add Multiples of the Direction Offsets for the Specific Piece
	std::vector<Move> psuedoLegalMoves;
	unsigned int pieceIndex{ 0 };

	// Up Down Left Right UpLeft UpRight DownLeft DownRight 
	std::array<int, 8> directionalOffsets64 = {-8, 8, -1, 1, -9, -7, 7, 9}; 
	std::array<int, 8> directionalOffsets120 = {-10, 10, -1, 1, -11, -9, 9, 11};


	//Clockwise
	std::array<int, 8> directionalOffsetsKnight64 = { -15, -6, 10, 17, 15, 6, -10, -17};
	std::array<int, 8> directionalOffsetsKnight120 = { -19, -8, 12, 21, 19, 8, -12, -21};

	//UpLeft UpRight DownLeft DownRight
	std::array<int, 8> directionalOffsetsBishop64 = { -9, -7, 7, 9 };
	std::array<int, 8> directionalOffsetsBishop120 = { -11, -9, 9, 11 };

	//Up Down Left Right
	std::array<int, 8> directionalOffsetsRook64 = { -8, 8, -1, 1 };
	std::array<int, 8> directionalOffsetsRook120 = { -10, 10, -1, 1 };

	//UpLeft UpRight
	std::array<int, 8> directionalOffsetsWhitePawn64 = { -9, -7};
	std::array<int, 8> directionalOffsetsWhitePawn120 = { -11, -9};

	//DownLeft DownRight
	std::array<int, 8> directionalOffsetsBlackPawn64 = { 7, 9 };
	std::array<int, 8> directionalOffsetsBlackPawn120 = { 9, 11 };

	for (auto& square : board) {

		if (square == empty) {
			pieceIndex++;
			continue;
		}
		
		switch (square) {
		case blackKing: {
			for (auto& directionalOffset120 : directionalOffsets120) {
				unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120] };

				if (finish64Index == 99) {
					continue;
				}

				if ((board[pieceIndex] * board[finish64Index]) <= 0) {
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });
				}

			}

			//Castling
			
			if (castlingAvailability.blackKingSide) {
				
				if (board[pieceIndex + 1] == empty && board[pieceIndex + 2] == empty) {
					
					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + 2] };
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index, {finish64Index + 1, finish64Index - 1, &castlingAvailability.blackKingSide } });
				}
			}

			if (castlingAvailability.blackQueenSide) {
				if (board[pieceIndex - 1] == empty && board[pieceIndex - 2] == empty && board[pieceIndex - 3] == empty) {
					
					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] - 2] };
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index, {finish64Index - 2 , finish64Index + 1, &castlingAvailability.blackQueenSide} });
				}
			}
			break;
		}
		case whiteKing: {
			for (auto& directionalOffset120 : directionalOffsets120) {
				unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120] };

				if (finish64Index == 99) {
					continue;
				}

				if ((board[pieceIndex] * board[finish64Index]) <= 0) {
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });
				}

			}

			//Castling

			if (castlingAvailability.whiteKingSide) {

				if (board[pieceIndex + 1] == empty && board[pieceIndex + 2] == empty) {

					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + 2] };
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index, {finish64Index + 1, finish64Index - 1, &castlingAvailability.whiteKingSide } });
				}
			}

			if (castlingAvailability.whiteQueenSide) {
				if (board[pieceIndex - 1] == empty && board[pieceIndex - 2] == empty && board[pieceIndex - 3] == empty) {

					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] - 2] };
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index, {finish64Index - 2 , finish64Index + 1, &castlingAvailability.whiteQueenSide} });
				}
			}

			break;
		}

		case blackKnight:
		case whiteKnight: {
			for (auto& directionalOffset120 : directionalOffsetsKnight120) {
				unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120] };

				if (finish64Index == 99) {
					continue;
				}

				if ((board[pieceIndex] * board[finish64Index]) <= 0) {
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });
				}

			}

			break;
		}
		case blackBishop:
		case whiteBishop: {
			for (auto& directionalOffset120 : directionalOffsetsBishop120) {


				//Bishop fun, probably another for loop

				for (unsigned int scalar = 1; scalar <= 8; scalar++) {
					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120 * scalar] };

					if (finish64Index == 99) {
						break;
					}

					if (board[finish64Index] * board[pieceIndex] > 0) {
						break;
					}
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

					//Checks if the Finish Square is an Opponent Piece
					if (board[finish64Index] * board[pieceIndex] < 0) {
						break;
					}
				}

			}

			break;
		}
		case blackRook:
		case whiteRook: {
			for (auto& directionalOffset120 : directionalOffsetsRook120) {
				unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120] };

				for (unsigned int scalar = 1; scalar <= 8; scalar++) {
					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120 * scalar] };

					if (finish64Index == 99) {
						break;
					}

					if (board[finish64Index] * board[pieceIndex] > 0) {
						break;
					}
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

					//Checks if the Finish Square is an Opponent Piece
					if (board[finish64Index] * board[pieceIndex] < 0) {
						break;
					}

				}

			}

			break;
		}
		case blackQueen:
		case whiteQueen: {
			for (auto& directionalOffset120 : directionalOffsetsBishop120) {


				//Bishop fun, probably another for loop

				for (unsigned int scalar = 1; scalar <= 8; scalar++) {
					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120 * scalar] };

					if (finish64Index == 99) {
						break;
					}

					if (board[finish64Index] * board[pieceIndex] > 0) {
						break;
					}
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

					//Checks if the Finish Square is an Opponent Piece
					if (board[finish64Index] * board[pieceIndex] < 0) {
						break;
					}
				}

			}

			for (auto& directionalOffset120 : directionalOffsetsRook120) {
				unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120] };

				for (unsigned int scalar = 1; scalar <= 8; scalar++) {
					unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffset120 * scalar] };

					if (finish64Index == 99) {
						break;
					}

					if (board[finish64Index] * board[pieceIndex] > 0) {
						break;
					}
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

					//Checks if the Finish Square is an Opponent Piece
					if (board[finish64Index] * board[pieceIndex] < 0) {
						break;
					}

				}

			}
			break;
		}
		case blackPawn: {
			//Down
			unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffsets120[1]] };

			if (board[finish64Index] == empty) {
				psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

				if (pieceIndex >= 8 && pieceIndex <= 15) {
					finish64Index += directionalOffsets64[1];

					if (board[finish64Index] == empty) {
						psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

					}
				}
			}

			//DownLeft DownRight
			for (auto& directionalOffset120 : directionalOffsetsBlackPawn120) {
				finish64Index = mailbox120[mailbox64[pieceIndex] + directionalOffset120];

				if (finish64Index == 99) {
					continue;
				}

				if (board[pieceIndex] * board[finish64Index] < 0) {
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });
				}
			}
			break;
		}
		case whitePawn: {
			//Up
			unsigned int finish64Index{ mailbox120[mailbox64[pieceIndex] + directionalOffsets120[0]] };

			if (board[finish64Index] == empty) {
				psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

				if (pieceIndex >= 48 && pieceIndex <= 55) {
					finish64Index += directionalOffsets64[0];

					if (board[finish64Index] == empty) {
						psuedoLegalMoves.push_back({ pieceIndex, finish64Index });

					}
				}
			}

			//UpLeft UpRight
			for (auto& directionalOffset120 : directionalOffsetsWhitePawn120) {
				finish64Index = mailbox120[mailbox64[pieceIndex] + directionalOffset120];
				
				if (finish64Index == 99) {
					continue;
				}

				if (board[pieceIndex] * board[finish64Index] < 0) {
					psuedoLegalMoves.push_back({ pieceIndex, finish64Index });
				}
			}
			break;
		}


		}

	pieceIndex++;
	}
	return psuedoLegalMoves;
}