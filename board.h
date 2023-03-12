#pragma once
#include <unordered_map>
#include <string>
#include <tuple>
#include <vector>
#include "piece.h"
#include "test.h"
#include <SFML/Graphics.hpp>

struct BoardConstructorArgs {
    std::string fen;
    bool drawBoardOnScreenEnabled;
    std::string texturePath;
};



class Board {

private:
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
    
    /*std::map<Pieces, std::unique_ptr<sf::Texture>> pieceToTextureDictionary;*/

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

    bool drawBoardOnScreenEnabled;
	Colour activeColour;
	CastlingAvailability castlingAvailability;
	unsigned int enpassant64Index;
	unsigned int halfmoveClock;
	unsigned int fullmoveNumber;
    std::vector<Piece> pieceSprites;

public:
    Board();
    Board(const BoardConstructorArgs args);
    std::unordered_map<Pieces, sf::Texture> pieceToTextureDictionary;
    void loadFEN(std::string fen);
    std::string getBoardAsFEN();

    unsigned int algebraicNotationTo64Index(std::string square);
    void updatePieceSprites();
    bool getDrawBoardOnScreenEnabled();
    std::vector<Piece> getPieceSprites();
    void displayBoard();
    void makeMove();
    void unmakeMove();

};

