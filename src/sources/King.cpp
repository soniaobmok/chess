#include "../headers/King.h"

King::King(unsigned char figureColor)
    : Figure('K', figureColor) {}

bool King::canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                      int destRow) {
  return !(destColumn > sourceColumn + 1 || destColumn < sourceColumn - 1 ||
           destRow > sourceRow + 1 || destRow < sourceRow - 1);
}

bool King::canBeMovedWithoutAttack(int sourceColumn, int sourceRow,
                                   int destColumn, int destRow) {
  return false;
}
