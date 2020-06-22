#include "Figure.h"

#ifndef CHESS_LUX_ROOK_H
#define CHESS_LUX_ROOK_H

class Rook : public Figure {
public:
  explicit Rook(unsigned char figureColor);

  bool canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                  int destRow) override;
  bool canBeMovedWithoutAttack(int sourceColumn, int sourceRow, int destColumn,
                               int destRow) override;
};

#endif // CHESS_LUX_ROOK_H
