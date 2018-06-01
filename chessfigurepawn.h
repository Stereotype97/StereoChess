#ifndef CHESSFIGUREPAWN_H
#define CHESSFIGUREPAWN_H
#include <chessfigure.h>

class ChessFigurePawn : public ChessFigure
{
    bool hasLongTurn;
public:
    ChessFigurePawn(Color col = Color::WHITE, Figure fig = Figure::PAWN);
    virtual QVector<QPair<QChar, int> > getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos);
};

#endif // CHESSFIGUREPAWN_H
