#ifndef CHESSFIGUREOFFICER_H
#define CHESSFIGUREOFFICER_H
#include "chessfigure.h"

class ChessFigureOfficer : public ChessFigure
{
public:
    ChessFigureOfficer(Color col = Color::WHITE, Figure fig = Figure::OFFICER);
};

#endif // CHESSFIGUREOFFICER_H
