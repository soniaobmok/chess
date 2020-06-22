#include "../headers/Rook.h"

Rook::Rook(unsigned char figureColor)
    : Figure('R', figureColor) {
  disableCastling();
}

bool Rook::canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                      int destRow) {
  if (destColumn == sourceColumn) { // vertical
    return true;
  } else if (destRow == sourceRow) { // horizontal
    return true;
  }
  return false;
}

bool Rook::canBeMovedWithoutAttack(int sourceColumn, int sourceRow,
                                   int destColumn, int destRow) {
  return false;
}
