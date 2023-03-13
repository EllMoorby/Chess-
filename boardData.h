#pragma once
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