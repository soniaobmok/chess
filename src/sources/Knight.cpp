#include "../headers/Knight.h"

Knight::Knight(unsigned char figureColor)
    : Figure('N', figureColor) {
  disableFirstMoveOption();
  disableCastling();
}

bool Knight::canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                        int destRow) {
  return (destColumn == sourceColumn + 1 &&
          (destRow == sourceRow + 2 || destRow == sourceRow - 2)) ||
         (destColumn == sourceColumn + 2 &&
          (destRow == sourceRow + 1 || destRow == sourceRow - 1)) ||
         (destColumn == sourceColumn - 1 &&
          (destRow == sourceRow + 2 || destRow == sourceRow - 2)) ||
         (destColumn == sourceColumn - 2 &&
          (destRow == sourceRow + 1 || destRow == sourceRow - 1));
}

bool Knight::canBeMovedWithoutAttack(int sourceColumn, int sourceRow,
                                     int destColumn, int destRow) {
  return false;
}
