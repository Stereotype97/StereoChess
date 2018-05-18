#include "cell.h"

ChessFigure Cell::getChessFigure() const
{
    return figure;
}

Cell::Cell()
{
    isEmpty = true;
}

void Cell::setChessFigure(ChessFigure f)
{
    figure = f;
    isEmpty = false;
}

bool Cell::isCellEmpty()
{
    return isEmpty;
}

void Cell::setCellEmpty()
{
    isEmpty = true;
}
