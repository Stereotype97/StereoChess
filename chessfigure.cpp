#include "chessfigure.h"

ChessFigure::ChessFigure(Figure fig, Color col) : figure(fig), color(col)
{

}

Figure ChessFigure::getFigure() const
{
    return figure;
}

void ChessFigure::setFigure(const Figure &value)
{
    figure = value;
}

Color ChessFigure::getColor() const
{
    return color;
}

void ChessFigure::setColor(const Color &value)
{
    color = value;
}

QPair<int, int> ChessFigure::getCastCoordFromNormal(QPair<QChar, int> currPos)
{
    QVector<QChar> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    QVector<int> helpIndex = {7, 6, 5, 4, 3, 2, 1, 0};

    QChar letter = currPos.first;
    int n = currPos.second;

    int first = 0, second = 0;
    if (color == Color::WHITE) {
        first = helpIndex[n - 1];
        second = letters.indexOf(letter);
    }
    else {
        first = n - 1;
        second = 8 - 1 - letters.indexOf(letter);
    }

    return qMakePair(first, second);
}

QPair<QChar, int> ChessFigure::getNormalCoordFromCast(QPair<int, int> currPos)
{
    QVector<QChar> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    QVector<int> helpIndex = {7, 6, 5, 4, 3, 2, 1, 0};

    int first = currPos.first;
    int second = currPos.second;

    QChar letter;
    int n;
    if (color == Color::WHITE) {
        letter = letters[second];
        n = helpIndex.indexOf(first) + 1;
    }
    else {
        letter = letters[8 - 1 - second];
        n = first + 1;
    }

    return qMakePair(letter, n);
}
