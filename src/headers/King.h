#include "Figure.h"

#ifndef CHESS_LUX_KING_H
#define CHESS_LUX_KING_H

class King : public Figure {
public:
  explicit King(unsigned char figureColor);

  bool canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                  int destRow) override;
  bool canBeMovedWithoutAttack(int sourceColumn, int sourceRow, int destColumn,
                               int destRow) override;
};

#endif // CHESS_LUX_KING_H
