#include <SFML/Graphics.hpp>
#include "board.h"
#include <iostream>

int main()
{
    Board board;
    board.loadFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 32 1 ");
    std::string test = board.getBoardAsFEN();
    return 0;
}