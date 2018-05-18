#ifndef CHESSFIGUREKNIGHT_H
#define CHESSFIGUREKNIGHT_H
#include "chessfigure.h"

class ChessFigureKnight : public ChessFigure
{
public:
    ChessFigureKnight(Color col = Color::WHITE, Figure fig = Figure::KNIGHT);
};

#endif // CHESSFIGUREKNIGHT_H
