#ifndef CHESSFIGUREKING_H
#define CHESSFIGUREKING_H
#include "chessfigure.h"

class ChessFigureKing : public ChessFigure
{
public:
    ChessFigureKing(Color col = Color::WHITE, Figure fig = Figure::KING);
    virtual QVector<QPair<QChar, int> > getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos);
};

#endif // CHESSFIGUREKING_H
