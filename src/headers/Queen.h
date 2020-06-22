#include "Figure.h"

#ifndef CHESS_LUX_QUEEN_H
#define CHESS_LUX_QUEEN_H

class Queen : public Figure {
public:
  explicit Queen(unsigned char figureColor);

  bool canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                  int destRow) override;
  bool canBeMovedWithoutAttack(int sourceColumn, int sourceRow, int destColumn,
                               int destRow) override;
};

#endif // CHESS_LUX_QUEEN_H
