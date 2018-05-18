#ifndef CHESSFIGUREBOAT_H
#define CHESSFIGUREBOAT_H
#include <chessfigure.h>

class ChessFigureBoat : public ChessFigure
{
public:
    ChessFigureBoat(Color col = Color::WHITE, Figure fig = Figure::BOAT);
};

#endif // CHESSFIGUREBOAT_H
