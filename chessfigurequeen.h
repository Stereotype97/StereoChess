#ifndef CHESSFIGUREQUEEN_H
#define CHESSFIGUREQUEEN_H
#include "chessfigure.h"

class ChessFigureQueen : public ChessFigure
{
public:
    ChessFigureQueen(Color col = Color::WHITE, Figure fig = Figure::QUEEN);
    virtual QVector<QPair<QChar, int> > getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos);
};

#endif // CHESSFIGUREQUEEN_H
