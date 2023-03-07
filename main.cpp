#include <SFML/Graphics.hpp>
#include "board.h"

int main()
{
    Board board;
    board.loadFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    board.displayBoard();
    return 0;
}