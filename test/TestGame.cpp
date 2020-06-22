#include "TestGame.h"

const int Width = 8;

Cell **TestGame::createEmptyBoard(int width) {
    Cell **board = new Cell *[width];
    for (int i = 0; i < width; i++) {
        board[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            board[i][j].setCoordinate(j + 'a', i + 1);
        }
    }
    return board;
}

void TestGame::deleteBoard(Cell **board) {
    for (int i = 0; i < Width; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void TestGame::testCoordinatesAreValid() {
    assert(Game::coordinatesAreValid("a1"));
    assert(Game::coordinatesAreValid("h8"));
    assert(!Game::coordinatesAreValid("a 1"));
    assert(!Game::coordinatesAreValid("h 8"));
    assert(!Game::coordinatesAreValid(" a1"));
    assert(!Game::coordinatesAreValid("h8 "));
    assert(!Game::coordinatesAreValid("h0"));
    assert(!Game::coordinatesAreValid("h9"));
    assert(!Game::coordinatesAreValid("i8"));
}

void TestGame::testMoveFigure() {
    Cell **board = createEmptyBoard(Width);

    board[2][6].setFigure(std::unique_ptr<Figure>(new Rook('W'))); // g3

    unsigned char color = board[2][6].getFigureColor();
    unsigned char type = board[2][6].getFigureType();

    Game::moveFigure(board[2][6], board[4][6]); // g5

    assert(!board[2][6].hasFigure());
    assert(board[4][6].hasFigure());
    assert(board[4][6].getFigureType() == type);
    assert(board[4][6].getFigureColor() == color);

    deleteBoard(board);
}

void TestGame::testCheckMate() {
    Cell **board1 = createEmptyBoard(Width);

    board1[7][0].setFigure(std::unique_ptr<Figure>(new King('B'))); // a8
    board1[5][0].setFigure(std::unique_ptr<Figure>(new Rook('W'))); // a6
    board1[4][1].setFigure(std::unique_ptr<Figure>(new Queen('W'))); // b5

    assert(Game::checkmate(board1[5][0], board1[7][0], board1));

    deleteBoard(board1);


    Cell **board2 = createEmptyBoard(Width);

    board2[7][0].setFigure(std::unique_ptr<Figure>(new King('B'))); // a8
    board2[5][0].setFigure(std::unique_ptr<Figure>(new Rook('W'))); // a6

    assert(!Game::checkmate(board2[5][0], board2[7][0], board2));

    deleteBoard(board2);


    Cell **board3 = createEmptyBoard(Width);

    board3[7][0].setFigure(std::unique_ptr<Figure>(new King('B'))); // a8
    board3[6][3].setFigure(std::unique_ptr<Figure>(new Rook('B'))); // d7
    board3[5][0].setFigure(std::unique_ptr<Figure>(new Rook('W'))); // a6
    board3[4][1].setFigure(std::unique_ptr<Figure>(new Queen('W'))); // b5

    assert(!Game::checkmate(board3[5][0], board3[7][0], board3));

    deleteBoard(board3);


    Cell **board4 = createEmptyBoard(Width);

    board4[7][0].setFigure(std::unique_ptr<Figure>(new King('B'))); // a8
    board3[7][2].setFigure(std::unique_ptr<Figure>(new Bishop('B'))); // c8
    board4[5][0].setFigure(std::unique_ptr<Figure>(new Rook('W'))); // a6
    board4[4][1].setFigure(std::unique_ptr<Figure>(new Queen('W'))); // b5

    assert(!Game::checkmate(board4[5][0], board4[7][0], board4));

    deleteBoard(board4);
}
