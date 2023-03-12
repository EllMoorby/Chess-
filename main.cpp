#include <SFML/Graphics.hpp>
#include "board.h"
#include "piece.h"
#include "chess.h"
#include <iostream>

int main()
{
    std::string texturePath = "assets/textures";

    Chess chess({480, 480, texturePath});
    chess.createWindow();
    chess.start();
    return 0;
}