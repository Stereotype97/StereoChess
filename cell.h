#ifndef CELL_H
#define CELL_H
#include "chessfigure.h"

//enum class Letter {A, B, C, D, E, F, G, H};

class Cell
{
public:
    Cell();
    void setChessFigure(ChessFigure *f);
    ChessFigure *getChessFigure() const;
    bool isCellEmpty();
    void setCellEmpty();
private:
    bool isEmpty;
    ChessFigure *figure;
    //std::optional - qt lazy type
//    bool QVariant::isNull() const
//    bool QVariant::isValid() const
//    Type QVariant::type()
//    static QVariant QVariant::fromValue(const T & value)
//    T QVariant::value()
};

#endif // CELL_H
