#include "../headers/Game.h"

#include <iostream>
#include <string>

const int Width = 8;
Game *savedGame = nullptr;
Game *loadedGame = nullptr;

Game::Game()
    : checkForWhite(false), checkForBlack(false), endGame(false),
      colorFlag(true) {
  board = new Cell *[Width];
  for (int i = 0; i < Width; i++) {
    board[i] = new Cell[Width];
    for (int j = 0; j < Width; j++) {
      board[i][j].setCoordinate(j + 'a', i + 1);
      board[i][j].fillCellOnStart();
    }
  }
}

void Game::printTable() {
  const unsigned char UpperLeft = 201;
  const unsigned char UpperRight = 187;
  const unsigned char LowerLeft = 200;
  const unsigned char LowerRight = 188;

  const unsigned char SimpleDoubleHorizontal = 205;
  const unsigned char UpperDoubleHorizontal = 209;
  const unsigned char LowerDoubleHorizontal = 207;

  const unsigned char SimpleDoubleVertical = 186;
  const unsigned char LeftDoubleVertical = 199;
  const unsigned char RightDoubleVertical = 182;

  const unsigned char Vertical = 179;
  const unsigned char Horizontal = 196;
  const unsigned char Cross = 197;
  const unsigned char FreeSpace = 32;

  unsigned char zeroChar = 48;

  // draw "White"
  std::cout << std::endl << "                  White" << std::endl;

  drawLetters();

  // draw upper line
  printLine(FreeSpace, UpperLeft, SimpleDoubleHorizontal, UpperDoubleHorizontal,
            UpperRight);

  // draw mid lines
  for (int i = 1; i < Width; i++) {
    // line 1
    std::cout << static_cast<char>(i + zeroChar);

    std::cout << SimpleDoubleVertical;

    for (int j = 0; j < Width - 1; j++) {
      printCell(i - 1, j, Vertical);
    }

    printCell(i - 1, 7, SimpleDoubleVertical);
    std::cout << static_cast<char>(i + zeroChar) << std::endl;

    // line 2
    printLine(FreeSpace, LeftDoubleVertical, Horizontal, Cross,
              RightDoubleVertical);
  }

  // draw line number 8
  std::cout << '8';
  std::cout << SimpleDoubleVertical;
  for (int j = 0; j < Width - 1; j++) {
    printCell(7, j, Vertical);
  }

  printCell(7, 7, SimpleDoubleVertical);
  std::cout << '8' << std::endl;

  // draw lower line
  printLine(FreeSpace, LowerLeft, SimpleDoubleHorizontal, LowerDoubleHorizontal,
            LowerRight);

  drawLetters();

  // draw "Black"
  std::cout << "                  Black" << std::endl << std::endl;
}

void Game::printLine(char rowNumber, unsigned char leftBorder,
                     unsigned char content, unsigned char cross,
                     unsigned char rightBorder) {
  std::cout << rowNumber;
  std::cout << leftBorder;
  for (int i = 1; i < Width; i++) {
    std::cout << content << content << content << content << cross;
  }
  std::cout << content << content << content << content << rightBorder
            << rowNumber << std::endl;
}

void Game::drawLetters() {
  unsigned char letterA = 97;

  std::cout << "   ";
  for (int i = 0; i < Width; i++) {
    std::cout << " " << letterA++ << "   ";
  }
  std::cout << std::endl;
}

void Game::startGame() {
  // main game cycle
  while (!endGame) {
    std::cout << "Choose the command (move, save, load, exit): ";
    std::cout << std::endl;

    std::string command;
    std::getline(std::cin, command);
    std::cout << std::endl;

    if (command == "move") {
      unsigned char currentColor;
      unsigned char enemyColor;

      currentColor = colorFlag ? 'W' : 'B';
      enemyColor = colorFlag ? 'B' : 'W';

      int sourceColumn = -1, sourceRow = -1;
      int destinationColumn = -1, destinationRow = -1;

      // check figure to move
      bool figureChecked = false;
      while (!figureChecked) {
        std::cout
            << "Which piece would you like to move? (for example \"a2\"): "
            << std::endl;
        std::string sourceCell;
        std::getline(std::cin, sourceCell);

        if (coordinatesAreValid(sourceCell)) {
          std::unique_ptr<cellCoordinate> sourceCellCoordinate(
              new cellCoordinate(sourceCell[0], sourceCell[1]));

          sourceColumn = sourceCellCoordinate->letter - 'a';
          sourceRow = sourceCellCoordinate->number - '1';

          if (board[sourceRow][sourceColumn].hasFigure() &&
              board[sourceRow][sourceColumn].getFigureColor() == currentColor) {
            figureChecked = true;
          } else {
            std::cout << "Figure was not checked!" << std::endl;
          }
        } else {
          std::cout << "Coordinates are not valid!" << std::endl;
        }
      }

      // check destination cell
      bool destinationChecked = false;
      while (!destinationChecked) {
        std::cout << "Where should the piece be moved?" << std::endl;
        std::string destinationCell;
        std::getline(std::cin, destinationCell);

        // check destination
        if (coordinatesAreValid(destinationCell)) {
          std::unique_ptr<cellCoordinate> destinationCellCoordinate(
              new cellCoordinate(destinationCell[0], destinationCell[1]));

          destinationColumn = destinationCellCoordinate->letter - 'a';
          destinationRow = destinationCellCoordinate->number - '1';

          if (!board[destinationRow][destinationColumn].hasFigure() ||
              board[destinationRow][destinationColumn].getFigureColor() != currentColor) {
            destinationChecked = true;
          } else {
            std::cout << "Destination was not checked!" << std::endl;
          }
        } else {
          std::cout << "Destination coordinates are not valid!" << std::endl;
        }
      }

      // move the figure
      if (Cell::canMoveFigure(board[sourceRow][sourceColumn],
                              board[destinationRow][destinationColumn], board)) {
        // if destCell has a figure we need to save it before moving and
        // checking
        Cell *temporaryFigureStorage = new Cell;
        if (board[destinationRow][destinationColumn].hasFigure()) {
          *temporaryFigureStorage = std::move(board[destinationRow][destinationColumn]);
        }

        // try to make a move
        moveFigure(board[sourceRow][sourceColumn],board[destinationRow][destinationColumn]);

        // check if move opened king to damage
        Cell *cellWithKing = Cell::findCellWithKing(board, currentColor);
        bool check = Cell::checkCellForDanger(*cellWithKing, board, currentColor);

        // return king to board
        int kingColumn = cellWithKing->getCoordinate().letter - 'a';
        int kingRow = cellWithKing->getCoordinate().number - 1;

        board[kingRow][kingColumn] = std::move(*cellWithKing);
        delete cellWithKing;

        // return attacking figure to sourceCell
        moveFigure(board[destinationRow][destinationColumn],board[sourceRow][sourceColumn]);

        // return saved figure to destinationCell
        if (temporaryFigureStorage->hasFigure()) {
          board[destinationRow][destinationColumn] = std::move(*temporaryFigureStorage);
        }
        delete temporaryFigureStorage;

        if (!check) {
          // if move is castling
          if (board[sourceRow][sourceColumn].getCastlingChecked() &&
              board[sourceRow][sourceColumn].getCastlingAbility()) {
            // castling
            if (destinationColumn == sourceColumn + 2) {
              Cell rookStartCell = std::move(board[sourceRow][7]);
              Cell rookFinishCell = std::move(board[sourceRow][5]);

              rookFinishCell.setFigure(std::move(rookStartCell.moveFigure())); // moved rook

              board[sourceRow][7] = std::move(rookStartCell);
              board[sourceRow][5] = std::move(rookFinishCell);
            } else {
              Cell rookStartCell = std::move(board[sourceRow][0]);
              Cell rookFinishCell = std::move(board[sourceRow][3]);

              rookFinishCell.setFigure(std::move(rookStartCell.moveFigure())); // moved rook

              board[sourceRow][0] = std::move(rookStartCell);
              board[sourceRow][3] = std::move(rookFinishCell);
            }

            board[sourceRow][sourceColumn].disableCastling();
          }

          // make a move
          moveFigure(board[sourceRow][sourceColumn],board[destinationRow][destinationColumn]);

          // removing check from current color
          switch (currentColor) {
          case 'W':
            checkForWhite = false;
            break;
          case 'B':
            checkForBlack = false;
            break;
          default:
            break;
          }

          // checking rules
          Cell *cellWithEnemyKing = Cell::findCellWithKing(board, enemyColor);
          bool checkToEnemy =
              Cell::checkCellForDanger(*cellWithEnemyKing, board, enemyColor);

          // return king to board
          int enemyKingColumn = cellWithEnemyKing->getCoordinate().letter - 'a';
          int enemyKingRow = cellWithEnemyKing->getCoordinate().number - 1;

          board[enemyKingRow][enemyKingColumn] = std::move(*cellWithEnemyKing);

          delete cellWithEnemyKing;

          if (checkToEnemy) {
            endGame = checkmate(board[destinationRow][destinationColumn],
                                board[enemyKingRow][enemyKingColumn], this->board);
          }

          // announcing check
          switch (currentColor) {
          case 'W':
            checkForBlack = checkToEnemy;
            break;
          case 'B':
            checkForWhite = checkToEnemy;
            break;
          default:
            break;
          }

          printTable();

          // check rules
          if (checkForWhite) {
            std::cout << "CHECK FOR WHITE!" << std::endl;
          }
          if (checkForBlack) {
            std::cout << "CHECK FOR BLACK!" << std::endl;
          }

          if (endGame) {
            std::cout << "CHECKMATE!" << std::endl;
          }

          // change color for next move
          colorFlag = !colorFlag;
        } else {
          std::cout << "Piece can't be moved here. Please try again."
                    << std::endl;
        }
      } else {
        std::cout << "Piece can't be moved here. Please try again."
                  << std::endl;
      }
    } else if (command == "save") {
      savedGame = new Game();

      savedGame->colorFlag = this->colorFlag;
      savedGame->endGame = this->endGame;
      savedGame->checkForWhite = this->checkForWhite;
      savedGame->checkForBlack = this->checkForBlack;

      for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Width; j++) {
          Cell *tempCell = Cell::copyForSaving(this->board[i][j]);

          savedGame->board[i][j] = std::move(*tempCell);

          delete tempCell;
        }
      }
      std::cout << "Game was successfully saved!" << std::endl;
    } else if (command == "load") {
      if (savedGame != nullptr) {

          loadedGame = new Game();

          loadedGame->colorFlag = savedGame->colorFlag;
          loadedGame->endGame = savedGame->endGame;
          loadedGame->checkForWhite = savedGame->checkForWhite;
          loadedGame->checkForBlack = savedGame->checkForBlack;

          for (int i = 0; i < Width; i++) {
              for (int j = 0; j < Width; j++) {
                  Cell *tempCell = Cell::copyForSaving(savedGame->board[i][j]);

                  loadedGame->board[i][j] = std::move(*tempCell);

                  delete tempCell;
              }
          }

        *this = *loadedGame;

        printTable();
        std::cout << "Loaded saved game!" << std::endl << std::endl;
      } else {
        std::cout << "Can't load! No saved game!" << std::endl << std::endl;
      }
    } else if (command == "exit") {
      endGame = true;
      std::cout << "Exit to main menu." << std::endl;
    }
  }
}

bool Game::coordinatesAreValid(std::string inputCoordinates) {
  if (inputCoordinates.size() != 2) {
    return false;
  }

  unsigned char letter = inputCoordinates[0];
  unsigned char number = inputCoordinates[1];
  return letter >= 'a' && letter <= 'h' && number >= '1' && number <= '8';
}

void Game::printCell(int row, int column, const unsigned char border) {
  if (board[row][column].hasFigure()) {
    std::cout << " " << board[row][column].getFigureColor()
              << board[row][column].getFigureType() << " " << border;
  } else {
    std::cout << "    " << border;
  }
}

void Game::moveFigure(Cell &sourceCell, Cell &destinationCell) {
  destinationCell.setFigure(std::move(sourceCell.moveFigure()));

  if (destinationCell.getFirstMoveOption()) {
    destinationCell.disableFirstMoveOption();
  }
}

bool Game::checkmate(Cell &damageCell, Cell &cellWithKing, Cell **board) {
  int damageCellColumn = damageCell.getCoordinate().letter - 'a';
  int damageCellRow = damageCell.getCoordinate().number - 1;

  // checking first way to avoid checkmate - if it is possible to remove
  // attacking figure
  for (int i = 0; i < Width; i++) {
    for (int j = 0; j < Width; j++) {
      if (board[i][j].hasFigure() &&
          Cell::canMoveFigure(board[i][j],board[damageCellRow][damageCellColumn], board)) {
        // save attacking figure
        Cell *temporaryFigureStorage = new Cell;
        if (board[damageCellRow][damageCellColumn].hasFigure()) { // unnecessary 'if', it always has figure
          *temporaryFigureStorage =std::move(board[damageCellRow][damageCellColumn]);
        }
        // moving defending figure to check next condition
        moveFigure(board[i][j],board[damageCellRow][damageCellColumn]); // moving

        // checking for check
        bool check = Cell::checkCellForDanger(cellWithKing, board, cellWithKing.getFigureColor());

        // moving  defending figure back
        moveFigure(board[damageCellRow][damageCellColumn], board[i][j]);

        // moving attacking figure back
        if (temporaryFigureStorage->hasFigure()) {
          board[damageCellRow][damageCellColumn] = std::move(*temporaryFigureStorage);
        }
        delete temporaryFigureStorage;

        if (!check) {
          return false;
        }
      }
    }
  }

  // checking second way to avoid checkmate - if it is possible to move king
  // away
  int kingCellColumn = cellWithKing.getCoordinate().letter - 'a';
  int kingCellRow = cellWithKing.getCoordinate().number - 1;

  for (int verticalOffset = -1; verticalOffset < 2; verticalOffset++) {
    for (int horizontalOffset = -1; horizontalOffset < 2; horizontalOffset++) {
      if ((kingCellRow + verticalOffset >= 0 && kingCellRow + verticalOffset <8) && // if checked coordinates are valid
          (kingCellColumn + horizontalOffset >= 0 && kingCellColumn + verticalOffset < 8) &&
          !board[kingCellRow + verticalOffset][kingCellColumn + horizontalOffset].hasFigure() && // if cell is empty
          !Cell::checkCellForDanger(board[kingCellRow + verticalOffset][kingCellColumn + horizontalOffset], // if cell is safe
              board, cellWithKing.getFigureColor())) {
        return false;
      }
    }
  }

  // checking third way to avoid checkmate - if it is possible to move a figure
  // between king and attacking figure
  if (damageCell.getFigureType() == 'N') {
    return true; // it is impossible to hide King from Knight
  } else {       // if other figures
    return !Cell::checkWay(damageCell, cellWithKing, board, Cell::checkWayToKing);
  }
}

Game::~Game() {
  for (int i = 0; i < Width; i++) {
    delete[] board[i];
  }
  delete[] board;
}
