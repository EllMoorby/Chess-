#include <SFML/Graphics.hpp>
#include "board.h"
#include "piece.h"
#include "chess.h"
#include <iostream>

int main()
{
    std::string texturePath = "assets/textures";
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Chess chess({480, 480, texturePath, fen});
    chess.start();
    return 0;
}