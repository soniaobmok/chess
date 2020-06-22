#include "Figure.h"

#ifndef CHESS_LUX_BISHOP_H
#define CHESS_LUX_BISHOP_H

class Bishop : public Figure {
public:
  explicit Bishop(unsigned char figureColor);

  bool canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                  int destRow) override;
  bool canBeMovedWithoutAttack(int sourceColumn, int sourceRow, int destColumn,
                               int destRow) override;
};

#endif // CHESS_LUX_BISHOP_H
