#include "chessfigureofficer.h"

ChessFigureOfficer::ChessFigureOfficer(Color col, Figure fig) : ChessFigure(fig, col)
{

}

QVector<QPair<QChar, int> > ChessFigureOfficer::getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos)
{

}
