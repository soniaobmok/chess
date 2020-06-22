#include "Figure.h"

#ifndef CHESS_LUX_KNIGHT_H
#define CHESS_LUX_KNIGHT_H

class Knight : public Figure {
public:
  explicit Knight(unsigned char figureColor);

  bool canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                  int destRow) override;
  bool canBeMovedWithoutAttack(int sourceColumn, int sourceRow, int destColumn,
                               int destRow) override;
};

#endif // CHESS_LUX_KNIGHT_H
