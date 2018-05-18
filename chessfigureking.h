#ifndef CHESSFIGUREKING_H
#define CHESSFIGUREKING_H
#include "chessfigure.h"

class ChessFigureKing : public ChessFigure
{
public:
    ChessFigureKing(Color col = Color::WHITE, Figure fig = Figure::KING);
};

#endif // CHESSFIGUREKING_H
