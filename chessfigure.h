#ifndef CHESSFIGURE_H
#define CHESSFIGURE_H
#include <QVector>
//#include <QPair>

enum class Figure {EMPTY, PAWN, KNIGHT, OFFICER, BOAT, QUEEN, KING};
enum class Color {WHITE, BLACK};

class ChessFigure
{
public:
    ChessFigure(Figure fig = Figure::EMPTY, Color col = Color::WHITE);
//    virtual QVector<QPair<QChar, int> > getPossibleTurns() = 0;
    Figure getFigure() const;
    void setFigure(const Figure &value);

    Color getColor() const;
    void setColor(const Color &value);

protected:
    Figure figure;
    Color color;
};

#endif // CHESSFIGURE_H
