#include "chessfigurepawn.h"
#include <QDebug>
ChessFigurePawn::ChessFigurePawn(Color col, Figure fig) : ChessFigure(fig, col)
{
    hasLongTurn = true;
}

QVector<QPair<QChar, int> > ChessFigurePawn::getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos)
{
    QVector<QPair<QChar, int> > turns;
    QPair<int, int> castCoord = getCastCoordFromNormal(currPos);
    qDebug() << castCoord;
    if ((color == Color::WHITE && currPos.second == 2) || (color == Color::BLACK && currPos.second == 7)) { //can do long turn
        if (field[castCoord.first - 2][castCoord.second] == 0)
            turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first - 2, castCoord.second)));
    }
    if (field[castCoord.first - 1][castCoord.second] == 0)
        turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first - 1, castCoord.second)));
    if (castCoord.second - 1 >= 0 && field[castCoord.first - 1][castCoord.second - 1] == 1)
        //check condition out of the range
        turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first - 1, castCoord.second - 1)));
    if (castCoord.second + 1 < 8 && field[castCoord.first - 1][castCoord.second + 1] == 1)
        turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first - 1, castCoord.second + 1)));

    qDebug() << turns;
    return turns;
}
