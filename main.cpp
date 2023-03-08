#include <SFML/Graphics.hpp>
#include "board.h"
#include "chess.h"
#include <iostream>

int main()
{
    Board board;
    board.loadFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq g6 32 1");
    board.displayBoard();
    std::string currentFen = board.getBoardAsFEN();
    std::cout << currentFen;
    std::string texturePath = "assets/textures";

    Chess chess({480, 480, texturePath });
    chess.createWindow();
    chess.start();


    return 0;
}