#include "../headers/Bishop.h"

#include <cstdlib>

Bishop::Bishop(unsigned char figureColor)
    : Figure('B', figureColor) {
  disableFirstMoveOption();
  disableCastling();
}

bool Bishop::canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                        int destRow) {
  return (abs(destColumn - sourceColumn) == abs(destRow - sourceRow));
}

bool Bishop::canBeMovedWithoutAttack(int sourceColumn, int sourceRow,
                                     int destColumn, int destRow) {
  return false;
}
