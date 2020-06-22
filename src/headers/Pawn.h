#include "Figure.h"

#ifndef CHESS_LUX_PAWN_H
#define CHESS_LUX_PAWN_H

class Pawn : public Figure {
public:
  explicit Pawn(unsigned char figureColor);

  bool canBeMovedWithoutAttack(int sourceColumn, int sourceRow, int destColumn,
                               int destRow) override;
  bool canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                  int destRow) override;
};

#endif // CHESS_LUX_PAWN_H
