#include "../headers/Figure.h"

Figure::Figure(unsigned char figureType, unsigned char figureColor)
    : color(figureColor), type(figureType) {
  this->firstMove = true;
  this->canCastle = true;
}

unsigned char Figure::getType() { return this->type; }

unsigned char Figure::getColor() { return this->color; }

void Figure::disableFirstMoveOption() { this->firstMove = false; }

void Figure::disableCastling() { this->canCastle = false; }

bool Figure::getFirstMove() { return this->firstMove; }

bool Figure::getCastlingAbility() { return this->canCastle; }
