#ifndef CHESSFIGUREPAWN_H
#define CHESSFIGUREPAWN_H
#include <chessfigure.h>

class ChessFigurePawn : public ChessFigure
{
public:
    ChessFigurePawn(Color col = Color::WHITE, Figure fig = Figure::PAWN);
};

#endif // CHESSFIGUREPAWN_H
