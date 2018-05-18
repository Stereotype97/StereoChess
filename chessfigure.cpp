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
