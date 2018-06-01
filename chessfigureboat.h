#ifndef CHESSFIGUREBOAT_H
#define CHESSFIGUREBOAT_H
#include <chessfigure.h>

class ChessFigureBoat : public ChessFigure
{
public:
    ChessFigureBoat(Color col = Color::WHITE, Figure fig = Figure::BOAT);
    virtual QVector<QPair<QChar, int> > getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos);
};

#endif // CHESSFIGUREBOAT_H
