#ifndef GAME_H
#define GAME_H
#include <QVector>
#include <cell.h>
#include <QObject>
#include "chessfigurepawn.h"
#include "chessfigureboat.h"
#include "chessfigureknight.h"
#include "chessfigureofficer.h"
#include "chessfigurequeen.h"
#include "chessfigureking.h"

class Game : public QObject
{
    Q_OBJECT

    QVector<QVector<Cell> > field;
public:
    explicit Game(QObject *parent = 0);
    QVector<QVector<Cell> > getField() const;

signals:
    void highlightFigure(QChar letter, int n, bool isTurnOn);
//    void needUpdate();
    void madeTurn(Figure figure, QChar fromLetter, int fromN, QChar whereLetter, int whereN);
public slots:
    void processCellClick(QChar letter, int n);
    void getColor(QString color);
    void setOpponentTurn(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN);
private:
    void initField();
    Cell &getCell(QChar letter, int n);
    void turn(QChar fromLetter, int fromN, QChar whereLetter, int whereN);
    QVector<QVector<short> > simplification();

    template <typename T>
    void rotateField(QVector<QVector<T> >& field_) {
        std::reverse(field_.begin(), field_.end());
        for (int i(0); i < field_.size(); i++) {
            std::reverse(field_[i].begin(), field_[i].end());
        }
    }

    QVector<int> correctIndex;
    QVector<QChar> helpLetters;

    bool isFigureChosen;
    QPair<QChar, int> currPos;
    Color myColor;
    QVector<QPair<QChar, int> > possibleTurns;
};

#endif // GAME_H
