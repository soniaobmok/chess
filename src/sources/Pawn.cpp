#include "../headers/Pawn.h"

Pawn::Pawn(unsigned char figureColor)
    : Figure('P', figureColor) {
  disableFirstMoveOption();
  disableCastling();
}

bool Pawn::canBeMovedWithoutAttack(int sourceColumn, int sourceRow,
                                   int destColumn,
                                   int destRow) { // vertical move
  if (this->getColor() == 'W') {
    if (sourceColumn != destColumn) {
      return false;
    }
    if (destRow == sourceRow + 1) {
      return true;
    }
    if (sourceRow == 1 && destRow == sourceRow + 2) {
      return true;
    }
  } else if (this->getColor() == 'B') {
    if (sourceColumn != destColumn) {
      return false;
    }
    if (destRow == sourceRow - 1) {
      return true;
    }
    if (sourceRow == 6 && destRow == sourceRow - 2) {
      return true;
    }
  }
  return false;
}

bool Pawn::canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                      int destRow) { // move with attack
  if (this->getColor() == 'W') {
    if (destRow == sourceRow + 1 &&
        (destColumn == sourceColumn + 1 || destColumn == sourceColumn - 1)) {
      return true;
    }
  } else if (this->getColor() == 'B') {
    if (destRow == sourceRow - 1 &&
        (destColumn == sourceColumn + 1 || destColumn == sourceColumn - 1)) {
      return true;
    }
  }
  return false;
}
