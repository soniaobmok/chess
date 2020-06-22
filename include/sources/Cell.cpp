#include "../headers/Cell.h"

#include <iostream>

const int Width = 8;

cellCoordinate::cellCoordinate(unsigned char letter, int number) {
  this->letter = letter;
  this->number = number;
}

unsigned char Cell::getFigureColor() { return this->figure->getColor(); }

unsigned char Cell::getFigureType() { return this->figure->getType(); }

bool Cell::hasFigure() { return this->figure != nullptr; }

cellCoordinate Cell::getCoordinate() { return this->coordinate; }

void Cell::setFigure(std::unique_ptr<Figure> movedFigure) {
  this->figure = std::move(movedFigure);
}

std::unique_ptr<Figure> Cell::moveFigure() { return std::move(this->figure); }

bool Cell::canMoveFigure(Cell &sourceCell, Cell &destinationCell, Cell **board) {
  int sourceColumn = sourceCell.getCoordinate().letter - 'a';
  int sourceRow = sourceCell.getCoordinate().number - 1;
  int destinationColumn = destinationCell.getCoordinate().letter - 'a';
  int destinationRow = destinationCell.getCoordinate().number - 1;

  if (sourceCell.getFigureType() == 'P' && destinationCell.hasFigure() // for pawn
      && destinationCell.getFigureColor() != sourceCell.getFigureColor()) {
    return sourceCell.figure->canBeMoved(sourceColumn, sourceRow, destinationColumn, destinationRow);

  } else if (sourceCell.getFigureType() == 'P') { // for pawn
    return sourceCell.figure->canBeMovedWithoutAttack(sourceColumn, sourceRow, destinationColumn, destinationRow);

  } else if (sourceCell.getFigureType() == 'N' && // for knight
             (!destinationCell.hasFigure() || destinationCell.getFigureColor() != sourceCell.getFigureColor())) {
    return sourceCell.figure->canBeMoved(sourceColumn, sourceRow, destinationColumn, destinationRow);

  } else if (sourceCell.getFigureType() == 'K' && destinationRow == sourceRow &&
             (destinationColumn == sourceColumn + 2 ||
              destinationColumn == sourceColumn - 2)) { // for castling

    if (!sourceCell.castlingChecked && canCastle(sourceCell, destinationCell, board)) {
      sourceCell.castlingChecked = true;
      return true;
    }
    return false;

  } else if (sourceCell.getFigureType() == 'K') { // for king
    if (!checkCellForDanger(destinationCell, board, sourceCell.getFigureColor())) {
      return sourceCell.figure->canBeMoved(sourceColumn, sourceRow, destinationColumn, destinationRow);
    }
  } else { // for queen, bishop, rook
    if (sourceCell.figure->canBeMoved(sourceColumn, sourceRow, destinationColumn, destinationRow)) {
      return !checkWay(sourceCell, destinationCell, board, checkForBarrier);
    }
  }
  return false;
}

bool Cell::checkWay(
    Cell &sourceCell, Cell &destinationCell, Cell **board,
    bool (*checkDirection)(int, int, int, int, int, int, Cell **)) { // if true - move is forbidden OR
  int sourceColumn = sourceCell.getCoordinate().letter - 'a'; // if true - no checkmate
  int sourceRow = sourceCell.getCoordinate().number - 1;
  int destinationColumn = destinationCell.getCoordinate().letter - 'a';
  int destinationRow = destinationCell.getCoordinate().number - 1;

  int checkedCellColumn = sourceColumn;
  int checkedCellRow = sourceRow;

  // diagonal check
  if (destinationColumn - sourceColumn > 0 && destinationRow - sourceRow > 0) { // down-right move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, 1, 1, board);

  } else if (destinationColumn - sourceColumn > 0 && destinationRow - sourceRow < 0) { // up-right move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, -1, 1, board);

  } else if (destinationColumn - sourceColumn < 0 && destinationRow - sourceRow < 0) { // up-left move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, -1, -1, board);

  } else if (destinationColumn - sourceColumn < 0 && destinationRow - sourceRow > 0) { // down-left move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, 1, -1, board);
  }

  // vertical check
  if (sourceColumn == destinationColumn && destinationRow - sourceRow > 0) { // down move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, 1, 0, board);

  } else if (sourceColumn == destinationColumn && destinationRow - sourceRow < 0) { // up move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, -1, 0, board);
  }

  // horizontal check
  if (sourceRow == destinationRow && destinationColumn - sourceColumn > 0) { // right move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, 0, 1, board);

  } else if (sourceRow == destinationRow && destinationColumn - sourceColumn < 0) { // left move
    return checkDirection(destinationColumn, destinationRow, checkedCellColumn,
                          checkedCellRow, 0, -1, board);
  }
  return true;
}

bool Cell::checkForBarrier(int destinationColumn,
                           int destinationRow, int checkedColumn,
                           int checkedRow, int verticalModifier,
                           int horizontalModifier, Cell **board) {
  checkedColumn += horizontalModifier;
  checkedRow += verticalModifier;

  if (verticalModifier != 0 && horizontalModifier != 0) {
    while ((destinationColumn - checkedColumn) * horizontalModifier > 0 &&
           (destinationRow - checkedRow) * verticalModifier > 0) {
      if (board[checkedRow][checkedColumn].hasFigure()) {
        return true;
      }
      checkedColumn += horizontalModifier;
      checkedRow += verticalModifier;
    }
  } else if (verticalModifier == 0) { // horizontal move
    while ((destinationColumn - checkedColumn) * horizontalModifier > 0) {
      if (board[checkedRow][checkedColumn].hasFigure()) {
        return true;
      }
      checkedColumn += horizontalModifier;
    }
  } else { // vertical move
    while ((destinationRow - checkedRow) * verticalModifier > 0) {
      if (board[checkedRow][checkedColumn].hasFigure()) {
        return true;
      }
      checkedRow += verticalModifier;
    }
  }
  return false;
}

void Cell::setCoordinate(unsigned char letter, int number) {
  this->coordinate.letter = letter;
  this->coordinate.number = number;
}

void Cell::fillCellOnStart() {
  switch (this->coordinate.number) {
  case 1:
    switch (this->coordinate.letter) {
    case 'a':
      this->figure = std::unique_ptr<Figure>(new Rook('W'));
      break;
    case 'b':
      this->figure = std::unique_ptr<Figure>(new Knight('W'));
      break;
    case 'c':
      this->figure = std::unique_ptr<Figure>(new Bishop('W'));
      break;
    case 'd':
      this->figure = std::unique_ptr<Figure>(new Queen('W'));
      break;
    case 'e':
      this->figure = std::unique_ptr<Figure>(new King('W'));
      break;
    case 'f':
      this->figure = std::unique_ptr<Figure>(new Bishop('W'));
      break;
    case 'g':
      this->figure = std::unique_ptr<Figure>(new Knight('W'));
      break;
    case 'h':
      this->figure = std::unique_ptr<Figure>(new Rook('W'));
      break;
    default:
      break;
    }
    break;
  case 2:
    this->figure = std::unique_ptr<Figure>(new Pawn('W'));
    break;
  case 7:
    this->figure = std::unique_ptr<Figure>(new Pawn('B'));
    break;
  case 8:
    switch (this->coordinate.letter) {
    case 'a':
      this->figure = std::unique_ptr<Figure>(new Rook('B'));
      break;
    case 'b':
      this->figure = std::unique_ptr<Figure>(new Knight('B'));
      break;
    case 'c':
      this->figure = std::unique_ptr<Figure>(new Bishop('B'));
      break;
    case 'd':
      this->figure = std::unique_ptr<Figure>(new Queen('B'));
      break;
    case 'e':
      this->figure = std::unique_ptr<Figure>(new King('B'));
      break;
    case 'f':
      this->figure = std::unique_ptr<Figure>(new Bishop('B'));
      break;
    case 'g':
      this->figure = std::unique_ptr<Figure>(new Knight('B'));
      break;
    case 'h':
      this->figure = std::unique_ptr<Figure>(new Rook('B'));
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

bool Cell::canCastle(Cell &sourceCell, Cell &destinationCell, Cell **board) {
  if (!sourceCell.getCastlingAbility() || !sourceCell.getFirstMoveOption()) {
    return false;
  }

  if (checkCellForDanger(destinationCell, board, sourceCell.getFigureColor())) {
    return false;
  }

  int sourceColumn = sourceCell.getCoordinate().letter - 'a';
  int sourceRow = sourceCell.getCoordinate().number - 1;

  int destinationColumn = destinationCell.getCoordinate().letter - 'a';

  Cell cellWithRook;

  if (destinationColumn == sourceColumn + 2) {
    // check for danger in passing cell
    Cell passingCell;
    passingCell = std::move(board[sourceRow][sourceColumn + 1]);

    if (checkCellForDanger(passingCell, board, sourceCell.getFigureColor())) { // if cell can be attacked
      return false;
    }

    // checking if if is first move
    cellWithRook = std::move(board[sourceRow][7]);

    if (!cellWithRook.getFirstMoveOption()) {
      board[sourceRow][7] = std::move(cellWithRook);
      return false;
    }

    // checking if there are other figures between king and rook
    if (checkWay(sourceCell, cellWithRook, board, checkForBarrier)) {
      board[sourceRow][7] = std::move(cellWithRook);
      return false;
    }

    board[sourceRow][7] = std::move(cellWithRook);
    return true;
  } else if (destinationColumn == sourceColumn - 2) {
    // check for danger in passing cell
    Cell passingCell;
    passingCell = std::move(board[sourceRow][sourceColumn - 1]);

    if (checkCellForDanger(passingCell, board, sourceCell.getFigureColor())) { // if cell can be attacked
      return false;
    }

    // checking if if is first move
    cellWithRook = std::move(board[0][sourceRow]);

    if (!cellWithRook.getFirstMoveOption()) {
      board[0][sourceRow] = std::move(cellWithRook);
      return false;
    }

    // checking if there are other figures between king and rook
    if (checkWay(sourceCell, cellWithRook, board, checkForBarrier)) {
      board[0][sourceRow] = std::move(cellWithRook);
      return false;
    }
    board[0][sourceRow] = std::move(cellWithRook);
    return true;
  }
  return false;
}

bool Cell::getCastlingAbility() { return this->figure->getCastlingAbility(); }

bool Cell::getFirstMoveOption() { return this->figure->getFirstMove(); }

void Cell::disableFirstMoveOption() { this->figure->disableFirstMoveOption(); }

bool Cell::checkCellForDanger(Cell &targetCell, Cell **board, unsigned char color) {
  Cell supposedDangerousCell;

  for (int i = 0; i < Width; i++) {
    for (int j = 0; j < Width; j++) {
      supposedDangerousCell = std::move(board[i][j]);

      if (supposedDangerousCell.hasFigure() &&
          supposedDangerousCell.getFigureColor() != color &&
          canMoveFigure(supposedDangerousCell, targetCell, board)) {
        board[i][j] = std::move(supposedDangerousCell);
        return true;
      }
      board[i][j] = std::move(supposedDangerousCell);
    }
  }
  return false;
}

Cell *Cell::findCellWithKing(Cell **board, unsigned char color) {
  Cell *cellWithKing = new Cell();
  for (int i = 0; i < Width; i++) {
    for (int j = 0; j < Width; j++) {
      if (board[i][j].hasFigure() && board[i][j].getFigureColor() == color &&
          board[i][j].getFigureType() == 'K') {
        *cellWithKing = std::move(board[i][j]);
        return cellWithKing;
      }
    }
  }
  return nullptr;
}

bool Cell::checkWayToKing(int destinationColumn, int destinationRow,
                          int checkedColumn, int checkedRow,
                          int verticalModifier, int horizontalModifier,
                          Cell **board) {
  checkedColumn += horizontalModifier;
  checkedRow += verticalModifier;

  unsigned char kingColor =
      board[destinationRow][destinationColumn].getFigureColor();

  if (verticalModifier != 0 && horizontalModifier != 0) {
    while ((destinationColumn - checkedColumn) * horizontalModifier > 0 &&
           (destinationRow - checkedRow) * verticalModifier > 0) {
      if (canMoveAnyFigureToCell(kingColor, checkedRow, checkedColumn, board)) {
        return true;
      }

      checkedColumn += horizontalModifier;
      checkedRow += verticalModifier;
    }
  } else if (verticalModifier == 0) { // horizontal move
    while ((destinationColumn - checkedColumn) * horizontalModifier > 0) {
      if (canMoveAnyFigureToCell(kingColor, checkedRow, checkedColumn, board)) {
        return true;
      }
      checkedColumn += horizontalModifier;
    }
  } else { // vertical move
    while ((destinationRow - checkedRow) * verticalModifier > 0) {
      if (canMoveAnyFigureToCell(kingColor, checkedRow, checkedColumn, board)) {
        return true;
      }
      checkedRow += verticalModifier;
    }
  }
  return false;
}

bool Cell::canMoveAnyFigureToCell(unsigned char figureColor, int destinationRow,
                                  int destinationColumn, Cell **board) {
  for (int i = 0; i < Width; i++) {
    for (int j = 0; j < Width; j++) {
      if (board[i][j].hasFigure() &&
          board[i][j].getFigureColor() == figureColor &&
          canMoveFigure(board[i][j], board[destinationRow][destinationColumn], board)) {
        return true;
      }
    }
  }
  return false;
}

Cell::Cell() : castlingChecked(false) {}

bool Cell::getCastlingChecked() { return this->castlingChecked; }

void Cell::disableCastling() { this->figure->disableCastling(); }

Cell *Cell::copyForSaving(Cell &sourceCell) {
  Cell *newCell = new Cell();

  newCell->castlingChecked = sourceCell.castlingChecked;

  newCell->coordinate.number = sourceCell.coordinate.number;
  newCell->coordinate.letter = sourceCell.coordinate.letter;

  if (!sourceCell.hasFigure()) {
    newCell->figure = nullptr;
  } else {
    switch (sourceCell.getFigureType()) {
    case 'P':
      newCell->figure =
          std::unique_ptr<Figure>(new Pawn(sourceCell.getFigureColor()));
      break;
    case 'R':
      newCell->figure =
          std::unique_ptr<Figure>(new Rook(sourceCell.getFigureColor()));
      break;
    case 'N':
      newCell->figure =
          std::unique_ptr<Figure>(new Knight(sourceCell.getFigureColor()));
      break;
    case 'B':
      newCell->figure =
          std::unique_ptr<Figure>(new Bishop(sourceCell.getFigureColor()));
      break;
    case 'Q':
      newCell->figure =
          std::unique_ptr<Figure>(new Queen(sourceCell.getFigureColor()));
      break;
    case 'K':
      newCell->figure =
          std::unique_ptr<Figure>(new King(sourceCell.getFigureColor()));
      break;
    default:
      break;
    }
  }
  return newCell;
}
