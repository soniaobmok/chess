#include "../headers/Queen.h"

#include <cstdlib>

Queen::Queen(unsigned char figureColor)
    : Figure('Q', figureColor) {
  disableFirstMoveOption();
  disableCastling();
}

bool Queen::canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                       int destRow) {
  if (abs(destColumn - sourceColumn) == abs(destRow - sourceRow)) { // diagonal
    return true;
  } else if (destColumn == sourceColumn) { // vertical
    return true;
  } else if (destRow == sourceRow) { // horizontal
    return true;
  }
  return false;
}

bool Queen::canBeMovedWithoutAttack(int sourceColumn, int sourceRow,
                                    int destColumn, int destRow) {
  return false;
}
