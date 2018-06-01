#include "chessfigureofficer.h"

ChessFigureOfficer::ChessFigureOfficer(Color col, Figure fig) : ChessFigure(fig, col)
{

}

QVector<QPair<QChar, int> > ChessFigureOfficer::getPossibleTurns(QVector<QVector<short> > field, QPair<QChar, int> currPos)
{
    QVector<QPair<QChar, int> > turns;
    QPair<int, int> castCoord = getCastCoordFromNormal(currPos);

    int temp_r = castCoord.first;
    int temp_c = castCoord.second;
    //move left-up
    while (temp_r - 1 >= 0 && temp_c - 1 >= 0 && field[temp_r - 1][temp_c - 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r - 1, temp_c - 1)));
        if (field[temp_r - 1][temp_c - 1] > 0) break;
        --temp_r;
        --temp_c;
    }

    temp_r = castCoord.first;
    temp_c = castCoord.second;
    //move left-down
    while (temp_r + 1 < 8 && temp_c - 1 >= 0 && field[temp_r + 1][temp_c - 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r + 1, temp_c - 1)));
        if (field[temp_r + 1][temp_c - 1] > 0) break;
        ++temp_r;
        --temp_c;
    }

    temp_r = castCoord.first;
    temp_c = castCoord.second;
    //move right-up
    while (temp_r - 1 >= 0 && temp_c + 1 < 8 && field[temp_r - 1][temp_c + 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r - 1, temp_c + 1)));
        if (field[temp_r - 1][temp_c + 1] > 0) break;
        --temp_r;
        ++temp_c;
    }

    temp_r = castCoord.first;
    temp_c = castCoord.second;
    //move right-down
    while (temp_r + 1 < 8 && temp_c + 1 < 8 && field[temp_r + 1][temp_c + 1] >= 0) { //empty cell and enemies figure
        turns.push_back(getNormalCoordFromCast(qMakePair(temp_r + 1, temp_c + 1)));
        if (field[temp_r + 1][temp_c + 1] > 0) break;
        ++temp_r;
        ++temp_c;
    }
    qDebug() << turns;

    return turns;
}
