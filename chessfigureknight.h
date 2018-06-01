#ifndef CHESSFIGUREKNIGHT_H
#define CHESSFIGUREKNIGHT_H
#include "chessfigure.h"

class ChessFigureKnight : public ChessFigure
{
public:
    ChessFigureKnight(Color col = Color::WHITE, Figure fig = Figure::KNIGHT);
    virtual QVector<QPair<QChar, int> > getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos);
};

#endif // CHESSFIGUREKNIGHT_H
