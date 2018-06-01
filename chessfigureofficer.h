#ifndef CHESSFIGUREOFFICER_H
#define CHESSFIGUREOFFICER_H
#include "chessfigure.h"

class ChessFigureOfficer : public ChessFigure
{
public:
    ChessFigureOfficer(Color col = Color::WHITE, Figure fig = Figure::OFFICER);
    virtual QVector<QPair<QChar, int> > getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos);
};

#endif // CHESSFIGUREOFFICER_H
