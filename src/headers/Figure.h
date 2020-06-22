#ifndef CHESS_LUX_FIGURE_H
#define CHESS_LUX_FIGURE_H

class Figure {
public:
  Figure(unsigned char figureType, unsigned char figureColor);

  unsigned char getType();
  unsigned char getColor();

  virtual bool canBeMoved(int sourceColumn, int sourceRow, int destColumn,
                          int destRow) = 0;
  virtual bool canBeMovedWithoutAttack(int sourceColumn, int sourceRow,
                                       int destColumn,
                                       int destRow) = 0; // only for pawn

  void disableFirstMoveOption();
  void disableCastling();

  bool getFirstMove();
  bool getCastlingAbility();

private:
  unsigned char type;
  unsigned char color;

  bool firstMove;
  bool canCastle;
};

#endif // CHESS_LUX_FIGURE_H
