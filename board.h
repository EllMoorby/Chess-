#pragma once
#include <string>

struct BoardConstructorArgs {
};

enum Colour {
    black,
    white
};

struct CastlingAvailability {
	bool whiteKingSide;
	bool whiteQueenSide;
	bool blackKingSide;
	bool blackQueenSide;

};

enum Pieces {
    blackKing = -6,
    blackQueen,
    blackRook,
    blackBishop,
    blackKnight,
    blackPawn,
    empty,
    whitePawn,
    whiteKnight,
    whiteBishop,
    whiteRook,
    whiteQueen,
    whiteKing
};

class Board {

private:
    const int mailbox120[120] = {
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99,  0,  1,  2,  3,  4,  5,  6,  7, 99,
     99,  8,  9, 10, 11, 12, 13, 14, 15, 99,
     99, 16, 17, 18, 19, 20, 21, 22, 23, 99,
     99, 24, 25, 26, 27, 28, 29, 30, 31, 99,
     99, 32, 33, 34, 35, 36, 37, 38, 39, 99,
     99, 40, 41, 42, 43, 44, 45, 46, 47, 99,
     99, 48, 49, 50, 51, 52, 53, 54, 55, 99,
     99, 56, 57, 58, 59, 60, 61, 62, 63, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99
    };

    const int mailbox64[64] = {
        21, 22, 23, 24, 25, 26, 27, 28,
        31, 32, 33, 34, 35, 36, 37, 38,
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78,
        81, 82, 83, 84, 85, 86, 87, 88,
        91, 92, 93, 94, 95, 96, 97, 98
    };

    Pieces board[64] = {
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty
    }; // 

	
	Colour activeColour;
	CastlingAvailability castlingAvailability;
	unsigned int enpassant64Index;
	unsigned int halfmoveClock;
	unsigned int fullmoveNumber;

public:
	Board();

    void loadFEN(std::string fen);
    std::string getBoardAsFEN();

    unsigned int algebraicNotationTo64Index(std::string square);
    void makeMove();
    void unmakeMove();

};

