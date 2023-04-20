#pragma once
#include <array>
#include <string>
#include <tuple>
#include <vector>
#include "piece.h"
#include "boardData.h"
#include <SFML/Graphics.hpp>

struct BoardConstructorArgs {
    std::string fen;
    bool drawBoardOnScreenEnabled;
    std::map<Pieces, sf::Texture> pieceToTextureDictionary;
};

struct CastlingRookMove {
    unsigned int castlingRookStartIndex64;
    unsigned int castlingRookFinishIndex64;
    bool* castlingRight;
};

struct Move {
    unsigned int startIndex64;
    unsigned int finishIndex64;
    CastlingRookMove castlingRookMove = { 99, 99 };
    
};

enum MovementOffsets {
    positiveXOffset120 = 1,
    positiveXOffset64 = 1,
    
    //Positive Y Offset Moves Down the Board
    positiveYOffset120 = 10,
    positiveYOffset64 = 8
};


class Board {

private:
    std::map<Pieces, sf::Texture> pieceToTextureDictionary;
    
    const std::array<unsigned int, 120> mailbox120 = {
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99,  0,  1,  2,  3,  4, 5,  6,  7, 99,
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

    const std::array<unsigned int, 64> mailbox64 = {
        21, 22, 23, 24, 25, 26, 27, 28,
        31, 32, 33, 34, 35, 36, 37, 38,
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78,
        81, 82, 83, 84, 85, 86, 87, 88,
        91, 92, 93, 94, 95, 96, 97, 98
    };

    std::array<Pieces, 64> board = {
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty,
        empty, empty, empty, empty, empty, empty, empty, empty
    }; // 

    bool drawBoardOnScreenEnabled;
    std::vector<Piece> pieceSprites;
    
    Colour activeColour;
	
	unsigned int enpassant64Index;
	unsigned int halfmoveClock;
	unsigned int fullmoveNumber;
    

public:
    Board();
    Board(const BoardConstructorArgs args);
    CastlingAvailability castlingAvailability;
    void initialiseTextures(std::string texturePath);
    
    void loadFEN(std::string fen);
    std::string getBoardAsFEN();
    
    unsigned int algebraicNotationTo64Index(std::string square);
    void updatePieceSprites();
    void displayBoard();
    void deleteAtIndex(unsigned int index);
    Pieces pieceAtIndex(unsigned int index);
    void addPieceToIndex(unsigned int index, Pieces piece);
    
    bool getDrawBoardOnScreenEnabled();
    std::vector<Piece> getPieceSprites();
    
    std::vector<Move> generatePsuedoLegalMoves();
    void makeMove();
    void unmakeMove();

};

