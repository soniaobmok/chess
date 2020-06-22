#include <cassert>
#include "../include/headers/Game.h"

#ifndef CHESS_TESTGAME_H
#define CHESS_TESTGAME_H


class TestGame {
public:
    static Cell **createEmptyBoard(int width);
    static void deleteBoard(Cell **board);

    static void testCoordinatesAreValid();
    static void testMoveFigure();
    static void testCheckMate();
};


#endif //CHESS_TESTGAME_H
