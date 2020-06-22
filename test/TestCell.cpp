#include <memory>
#include "TestCell.h"

const int Width = 8;

Cell **TestCell::createEmptyBoard(int width) {
    Cell **board = new Cell *[width];
    for (int i = 0; i < width; i++) {
        board[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            board[i][j].setCoordinate(j + 'a', i + 1);
        }
    }
    return board;
}

void TestCell::deleteBoard(Cell **board) {
    for (int i = 0; i < Width; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void TestCell::testGetFigureColor() {
    std::unique_ptr<Cell> cell1(new Cell());
    cell1->setCoordinate('a', 1);
    cell1->fillCellOnStart();
    assert(cell1->getFigureColor() == 'W');

    std::unique_ptr<Cell> cell2(new Cell());
    cell2->setCoordinate('a', 7);
    cell2->fillCellOnStart();
    assert(cell2->getFigureColor() == 'B');
}

void TestCell::testGetFigureType() {
    std::unique_ptr<Cell> cell1(new Cell());
    cell1->setCoordinate('a', 1);
    cell1->fillCellOnStart();
    assert(cell1->getFigureType() == 'R');

    std::unique_ptr<Cell> cell2(new Cell());
    cell2->setCoordinate('a', 7);
    cell2->fillCellOnStart();
    assert(cell2->getFigureType() == 'P');

    std::unique_ptr<Cell> cell3(new Cell());
    cell3->setCoordinate('e', 1);
    cell3->fillCellOnStart();
    assert(cell3->getFigureType() == 'K');
}

void TestCell::testHasFigure() {
    std::unique_ptr<Cell> cell1(new Cell());
    cell1->setCoordinate('a', 1);
    cell1->fillCellOnStart();
    assert(cell1->hasFigure());

    std::unique_ptr<Cell> cell2(new Cell());
    cell2->setCoordinate('a', 3);
    cell2->fillCellOnStart();
    assert(!cell2->hasFigure());

    std::unique_ptr<Cell> cell3(new Cell());
    cell3->setCoordinate('b', 7);
    assert(!cell3->hasFigure());
}

void TestCell::testCanMoveFigure() {
    Cell **board = TestCell::createEmptyBoard(Width);

    board[1][1].setFigure(std::unique_ptr<Figure>(new Pawn('W'))); // b2
    board[2][0].setFigure(std::unique_ptr<Figure>(new Pawn('B'))); // a3

    assert(Cell::canMoveFigure(board[1][1], board[2][1], board)); // b3
    assert(Cell::canMoveFigure(board[1][1], board[3][1], board)); // b4
    assert(Cell::canMoveFigure(board[1][1], board[2][0], board)); // a3
    assert(!Cell::canMoveFigure(board[1][1], board[0][1], board)); // b1
    assert(!Cell::canMoveFigure(board[1][1], board[1][2], board)); // c2
    assert(!Cell::canMoveFigure(board[1][1], board[2][2], board)); // c3

    board[4][2].setFigure(std::unique_ptr<Figure>(new Queen('W'))); // c5

    assert(Cell::canMoveFigure(board[4][2], board[2][0], board)); // a3
    assert(Cell::canMoveFigure(board[4][2], board[1][5], board)); // f2
    assert(Cell::canMoveFigure(board[4][2], board[4][0], board)); // a5
    assert(Cell::canMoveFigure(board[4][2], board[1][2], board)); // c2
    assert(!Cell::canMoveFigure(board[4][2], board[2][1], board)); // b3

    board[2][6].setFigure(std::unique_ptr<Figure>(new Rook('W'))); // g3

    assert(Cell::canMoveFigure(board[2][6], board[4][6], board)); // g5
    assert(Cell::canMoveFigure(board[2][6], board[2][7], board)); // h3
    assert(!Cell::canMoveFigure(board[2][6], board[3][7], board)); // h4
    assert(!Cell::canMoveFigure(board[2][6], board[4][7], board)); // h5

    board[6][1].setFigure(std::unique_ptr<Figure>(new Bishop('W'))); // b7

    assert(Cell::canMoveFigure(board[6][1], board[5][2], board)); // c6
    assert(Cell::canMoveFigure(board[6][1], board[7][2], board)); // c8
    assert(!Cell::canMoveFigure(board[6][1], board[6][5], board)); // f7
    assert(!Cell::canMoveFigure(board[6][1], board[5][3], board)); // d6

    board[0][4].setFigure(std::unique_ptr<Figure>(new King('W'))); // e1
    board[0][7].setFigure(std::unique_ptr<Figure>(new Rook('W'))); // h1

    assert(Cell::canMoveFigure(board[0][4], board[0][6], board)); // g1 //castling
    assert(Cell::canMoveFigure(board[0][4], board[0][3], board)); // d1
    assert(Cell::canMoveFigure(board[0][4], board[1][4], board)); // e2
    assert(Cell::canMoveFigure(board[0][4], board[1][3], board)); // d2
    assert(!Cell::canMoveFigure(board[0][4], board[0][2], board)); // c1
    assert(!Cell::canMoveFigure(board[0][4], board[2][4], board)); // e3
    assert(!Cell::canMoveFigure(board[0][4], board[1][0], board)); // a2

    board[7][6].setFigure(std::unique_ptr<Figure>(new Knight('W'))); // g8

    assert(Cell::canMoveFigure(board[7][6], board[5][5], board)); // f6
    assert(Cell::canMoveFigure(board[7][6], board[6][4], board)); // e7
    assert(!Cell::canMoveFigure(board[7][6], board[6][5], board)); // f7
    assert(!Cell::canMoveFigure(board[7][6], board[4][7], board)); // h5

    TestCell::deleteBoard(board);
}

void TestCell::testCheckWay() {
    Cell **board = createEmptyBoard(Width);

    board[5][1].setFigure(std::unique_ptr<Figure>(new Queen('W'))); // b6
    board[5][4].setFigure(std::unique_ptr<Figure>(new Pawn('W'))); // e6
    board[2][4].setFigure(std::unique_ptr<Figure>(new Knight('W'))); // e3

    assert(!Cell::checkWay(board[5][1], board[5][3], board, Cell::checkForBarrier)); // d6
    assert(!Cell::checkWay(board[5][1], board[3][3], board, Cell::checkForBarrier)); // d4
    assert(Cell::checkWay(board[5][1], board[5][5], board, Cell::checkForBarrier)); // f6
    assert(Cell::checkWay(board[5][1], board[1][5], board, Cell::checkForBarrier)); // f2

    TestCell::deleteBoard(board);
}

void TestCell::testCheckCellForDanger() {
    Cell **board = createEmptyBoard(Width);

    board[5][1].setFigure(std::unique_ptr<Figure>(new Queen('W'))); // b6

    assert(Cell::checkCellForDanger(board[5][3], board, 'B')); // d6
    assert(Cell::checkCellForDanger(board[3][3], board, 'B')); // d4
    assert(!Cell::checkCellForDanger(board[4][0], board, 'W')); // a5
    assert(!Cell::checkCellForDanger(board[1][2], board, 'B')); // c2

    TestCell::deleteBoard(board);
}

void TestCell::testCanMoveAnyFigureToCell() {
    Cell **board = createEmptyBoard(Width);

    board[5][1].setFigure(std::unique_ptr<Figure>(new Queen('W'))); // b6
    board[2][4].setFigure(std::unique_ptr<Figure>(new Knight('W'))); // e3

    assert(Cell::canMoveAnyFigureToCell('W', 3, 6, board)); // g4
    assert(Cell::canMoveAnyFigureToCell('W', 4, 2, board)); // c5
    assert(!Cell::canMoveAnyFigureToCell('W', 7, 0, board)); // a8

    TestCell::deleteBoard(board);
}

void TestCell::testFindCellWithKing() {
    Cell **board = createEmptyBoard(Width);

    board[0][4].setFigure(std::unique_ptr<Figure>(new King('W'))); // e1

    Cell *cellWithKing = Cell::findCellWithKing(board, 'W');

    assert(cellWithKing->getCoordinate().letter == 4 + 'a');
    assert(cellWithKing->getCoordinate().number == 0 + 1);

    delete cellWithKing;
    TestCell::deleteBoard(board);
}

void TestCell::testCopyForSaving() {
    Cell *cell = new Cell();
    cell->setCoordinate('b', 5);
    cell->setFigure(std::unique_ptr<Figure>(new Pawn('W')));

    Cell *copyCell = Cell::copyForSaving(*cell);

    assert(copyCell->getCoordinate().number == cell->getCoordinate().number);
    assert(copyCell->getCoordinate().letter == cell->getCoordinate().letter);
    assert(copyCell->getFigureType() == cell->getFigureType());
    assert(copyCell->getFigureColor() == cell->getFigureColor());

    delete copyCell;
    delete cell;
}

void TestCell::testMoveFigure() {
    Cell *cell = new Cell();
    cell->setCoordinate('b', 5);
    cell->setFigure(std::unique_ptr<Figure>(new Pawn('W')));

    Cell *copyCell = Cell::copyForSaving(*cell);

    std::unique_ptr<Figure> movedFigure = cell->moveFigure();

    assert(movedFigure->getColor() == copyCell->getFigureColor());
    assert(movedFigure->getType() == copyCell->getFigureType());

    delete copyCell;
    delete cell;
}

void TestCell::testSetFigure() {
    Cell *destinationCell = new Cell();
    destinationCell->setFigure(nullptr);

    std::unique_ptr<Figure> movedFigure = std::unique_ptr<Figure>(new Pawn('W'));

    unsigned char color = movedFigure->getColor();
    unsigned char type = movedFigure->getType();

    destinationCell->setFigure(std::move(movedFigure));

    assert(destinationCell->hasFigure());
    assert(destinationCell->getFigureType() == type);
    assert(destinationCell->getFigureColor() == color);

    delete destinationCell;
}



