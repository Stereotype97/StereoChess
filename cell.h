#ifndef CELL_H
#define CELL_H
#include "chessfigure.h"

//enum class CellSide{WHITE, BLACK};
enum class Letter {A, B, C, D, E, F, G, H};

class Cell
{
    ChessFigure figure;
public:
    Cell();
    void setChessFigure(ChessFigure f);
    ChessFigure getChessFigure() const;
    bool isCellEmpty();
    void setCellEmpty();
private:
    bool isEmpty;
};

#endif // CELL_H
