#include "chessfigureboat.h"

ChessFigureBoat::ChessFigureBoat(Color col, Figure fig) : ChessFigure(fig, col)
{

}

QVector<QPair<QChar, int> > ChessFigureBoat::getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos)
{
    QVector<QPair<QChar, int> > turns;
    QPair<int, int> castCoord = getCastCoordFromNormal(currPos);

    int temp = castCoord.second;
    //move left - change second
    while (temp - 1 >= 0 && field[castCoord.first][temp - 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first, temp - 1)));
        if (field[castCoord.first][temp - 1] > 0) break;
        --temp;
    }

    temp = castCoord.second;
    //move right - change second
    while (temp + 1 < 8 && field[castCoord.first][temp + 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first, temp + 1)));
        if (field[castCoord.first][temp + 1] > 0) break;
        ++temp;
    }

    temp = castCoord.first;
    //move up - change first
    while (temp - 1 >= 0 && field[temp - 1][castCoord.second] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp - 1, castCoord.second)));
        if (field[temp - 1][castCoord.second] > 0) break;
        --temp;
    }

    temp = castCoord.first;
    //move down - change first
    while (temp + 1 < 8 && field[temp + 1][castCoord.second] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp + 1, castCoord.second)));
        if (field[temp + 1][castCoord.second] > 0) break;
        ++temp;
    }
    qDebug() << turns;

    return turns;
}
