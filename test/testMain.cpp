#include <iostream>

#include "TestCell.h"
#include "TestGame.h"

int main() {
    std::cout << "Testing..." << std::endl;

    TestGame::testCoordinatesAreValid();
    TestGame::testMoveFigure();
    TestGame::testCheckMate();

    TestCell::testGetFigureColor();
    TestCell::testGetFigureType();
    TestCell::testHasFigure();
    TestCell::testCanMoveFigure();
    TestCell::testCheckWay();
    TestCell::testCheckCellForDanger();
    TestCell::testCanMoveAnyFigureToCell();
    TestCell::testFindCellWithKing();
    TestCell::testCopyForSaving();
    TestCell::testMoveFigure();
    TestCell::testSetFigure();

    return 0;
}