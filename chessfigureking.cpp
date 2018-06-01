#include "chessfigureking.h"

ChessFigureKing::ChessFigureKing(Color col, Figure fig) : ChessFigure(fig, col)
{

}

QVector<QPair<QChar, int> > ChessFigureKing::getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos)
{
    QVector<QPair<QChar, int> > turns;
    QPair<int, int> castCoord = getCastCoordFromNormal(currPos);

    int temp = castCoord.second;
    //move left - change second
    if (temp - 1 >= 0 && field[castCoord.first][temp - 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first, temp - 1)));
    }

    temp = castCoord.second;
    //move right - change second
    if (temp + 1 < 8 && field[castCoord.first][temp + 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(castCoord.first, temp + 1)));
    }

    temp = castCoord.first;
    //move up - change first
    if (temp - 1 >= 0 && field[temp - 1][castCoord.second] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp - 1, castCoord.second)));
    }

    temp = castCoord.first;
    //move down - change first
    if (temp + 1 < 8 && field[temp + 1][castCoord.second] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp + 1, castCoord.second)));
    }

    int temp_r = castCoord.first;
    int temp_c = castCoord.second;
    //move left-up
    if (temp_r - 1 >= 0 && temp_c - 1 >= 0 && field[temp_r - 1][temp_c - 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r - 1, temp_c - 1)));
    }

    temp_r = castCoord.first;
    temp_c = castCoord.second;
    //move left-down
    if (temp_r + 1 < 8 && temp_c - 1 >= 0 && field[temp_r + 1][temp_c - 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r + 1, temp_c - 1)));
    }

    temp_r = castCoord.first;
    temp_c = castCoord.second;
    //move right-up
    if (temp_r - 1 >= 0 && temp_c + 1 < 8 && field[temp_r - 1][temp_c + 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r - 1, temp_c + 1)));
    }

    temp_r = castCoord.first;
    temp_c = castCoord.second;
    //move right-down
    if (temp_r + 1 < 8 && temp_c + 1 < 8 && field[temp_r + 1][temp_c + 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r + 1, temp_c + 1)));
    }

    qDebug() << turns;

    return turns;
}
