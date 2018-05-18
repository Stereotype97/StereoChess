#ifndef CHESSFIGUREQUEEN_H
#define CHESSFIGUREQUEEN_H
#include "chessfigure.h"

class ChessFigureQueen : public ChessFigure
{
public:
    ChessFigureQueen(Color col = Color::WHITE, Figure fig = Figure::QUEEN);
};

#endif // CHESSFIGUREQUEEN_H
