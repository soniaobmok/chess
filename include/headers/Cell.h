#include <memory>

#include "../../src/headers/Bishop.h"
#include "../../src/headers/King.h"
#include "../../src/headers/Knight.h"
#include "../../src/headers/Pawn.h"
#include "../../src/headers/Queen.h"
#include "../../src/headers/Rook.h"

#ifndef CHESS_LUX_CELL_H
#define CHESS_LUX_CELL_H

struct cellCoordinate {
  cellCoordinate() = default;
  cellCoordinate(unsigned char letter, int number);
  unsigned char letter;
  int number;
};

class Cell {
public:
  Cell();

  cellCoordinate getCoordinate();

  void setCoordinate(unsigned char letter, int number);
  void fillCellOnStart();

  unsigned char getFigureColor();

  unsigned char getFigureType();
  bool hasFigure();

  bool getCastlingAbility();

  bool getFirstMoveOption();
  void disableFirstMoveOption();
  bool getCastlingChecked();

  void disableCastling();
  static bool canMoveFigure(Cell &sourceCell, Cell &destinationCell,
                            Cell **board);

  static bool checkWay(Cell &sourceCell, Cell &destinationCell, Cell **board,
                       bool (*checkDirection)(int, int, int, int, int, int,
                                              Cell **));
  static bool checkForBarrier(int destinationColumn,
                              int destinationRow,
                              int checkedColumn, int checkedRow,
                              int verticalModifier,
                              int horizontalModifier,
                              Cell **board);
  static bool checkWayToKing(int destinationColumn, int destinationRow,
                             int checkedColumn, int checkedRow,
                             int verticalModifier, int horizontalModifier,
                             Cell **board);
  static bool checkCellForDanger(Cell &targetCell, Cell **board,
                                 unsigned char color);
  static bool canCastle(Cell &sourceCell, Cell &destinationCell, Cell **board);
  static bool canMoveAnyFigureToCell(unsigned char figureColor,
                                     int destinationRow, int destinationColumn,
                                     Cell **board);

  static Cell *findCellWithKing(Cell **board, unsigned char color);

  void setFigure(std::unique_ptr<Figure> movedFigure);

  std::unique_ptr<Figure> moveFigure();

  static Cell *copyForSaving(Cell &sourceCell);

private:
  cellCoordinate coordinate;
  std::unique_ptr<Figure> figure;

  bool castlingChecked;
};

#endif // CHESS_LUX_CELL_H
