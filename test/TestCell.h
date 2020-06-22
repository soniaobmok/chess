#include "../include/headers/Cell.h"
#include <cassert>

#ifndef CHESS_TESTCELL_H
#define CHESS_TESTCELL_H


class TestCell {
public:
    static Cell **createEmptyBoard(int width);
    static void deleteBoard(Cell **board);

    static void testGetFigureColor();
    static void testGetFigureType();
    static void testHasFigure();
    static void testCanMoveFigure();
    static void testCheckWay();
    static void testCheckCellForDanger();
    static void testCanMoveAnyFigureToCell();
    static void testFindCellWithKing();
    static void testCopyForSaving();
    static void testMoveFigure();
    static void testSetFigure();
};


#endif //CHESS_TESTCELL_H
