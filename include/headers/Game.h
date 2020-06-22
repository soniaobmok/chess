#include "Cell.h"

#ifndef CHESS_LUX_GAME_H
#define CHESS_LUX_GAME_H

class Game {
public:
  Game();
  ~Game();

  static void drawLetters();
  static void printLine(char rowNumber, unsigned char leftBorder,
                        unsigned char content, unsigned char cross,
                        unsigned char rightBorder);
  void printCell(int row, int column, unsigned char border);
  void printTable();

  void startGame();

  static bool coordinatesAreValid(std::string inputCoordinates);

  static void moveFigure(Cell &sourceCell, Cell &destinationCell);

  static bool checkmate(Cell &damageCell, Cell &cellWithKing, Cell **board);

private:
  Cell **board;

  bool checkForWhite;
  bool checkForBlack;

  bool endGame;
  bool colorFlag;
};

#endif // CHESS_LUX_GAME_H
