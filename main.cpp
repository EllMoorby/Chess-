#include <SFML/Graphics.hpp>
#include "board.h"
#include "piece.h"
#include "chess.h"
#include <iostream>

int main()
{
    std::string texturePath = "assets/textures";

    Chess chess({480, 480, texturePath });
    chess.board.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    chess.board.displayBoard();
    Piece testPiece({ 0, blackKing, chess.blackKingImg });
    chess.createWindow();
    chess.start(testPiece);


    return 0;
}