#include "game.h"
#include <QDebug>

QVector<QVector<Cell> > Game::getField() const
{
    return field;
}

Game::Game(QObject *parent) : QObject(parent), correctIndex(QVector<int>(8))
{
    field.resize(8);
    for (int i(0); i < 8; i++) {
        field[i].resize(8);
    }
    helpLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    std::iota(correctIndex.begin(), correctIndex.end(), 0);
    std::reverse(correctIndex.begin(), correctIndex.end());
    initField();
    isFigureChosen = false;
    myColor = Color::WHITE;
}

void Game::initField()
{
    qDebug() << "init";
    getCell(QChar('a'), 1).setChessFigure(ChessFigureBoat(Color::WHITE));
    getCell(QChar('a'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));

    getCell(QChar('b'), 1).setChessFigure(ChessFigureKnight(Color::WHITE));
    getCell(QChar('b'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));

    getCell(QChar('c'), 1).setChessFigure(ChessFigureOfficer(Color::WHITE));
    getCell(QChar('c'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));

    getCell(QChar('d'), 1).setChessFigure(ChessFigureQueen(Color::WHITE));
    getCell(QChar('d'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));

    getCell(QChar('e'), 1).setChessFigure(ChessFigureKing(Color::WHITE));
    getCell(QChar('e'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));

    getCell(QChar('f'), 1).setChessFigure(ChessFigureOfficer(Color::WHITE));
    getCell(QChar('f'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));

    getCell(QChar('g'), 1).setChessFigure(ChessFigureKnight(Color::WHITE));
    getCell(QChar('g'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));

    getCell(QChar('h'), 1).setChessFigure(ChessFigureBoat(Color::WHITE));
    getCell(QChar('h'), 2).setChessFigure(ChessFigurePawn(Color::WHITE));
    //////////////////////////////////////////////////////////////////////////////
    getCell(QChar('a'), 8).setChessFigure(ChessFigureBoat(Color::BLACK));
    getCell(QChar('a'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));

    getCell(QChar('b'), 8).setChessFigure(ChessFigureKnight(Color::BLACK));
    getCell(QChar('b'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));

    getCell(QChar('c'), 8).setChessFigure(ChessFigureOfficer(Color::BLACK));
    getCell(QChar('c'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));

    getCell(QChar('d'), 8).setChessFigure(ChessFigureQueen(Color::BLACK));
    getCell(QChar('d'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));

    getCell(QChar('e'), 8).setChessFigure(ChessFigureKing(Color::BLACK));
    getCell(QChar('e'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));

    getCell(QChar('f'), 8).setChessFigure(ChessFigureOfficer(Color::BLACK));
    getCell(QChar('f'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));

    getCell(QChar('g'), 8).setChessFigure(ChessFigureKnight(Color::BLACK));
    getCell(QChar('g'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));

    getCell(QChar('h'), 8).setChessFigure(ChessFigureBoat(Color::BLACK));
    getCell(QChar('h'), 7).setChessFigure(ChessFigurePawn(Color::BLACK));
}

void Game::processCellClick(QChar letter, int n) //logic
{
    qDebug() << letter << n;
    QPair<QChar, int> currClick = qMakePair(letter, n);
    if (!isFigureChosen) {
        if (getCell(letter, n).isCellEmpty()) return;
        else if (getCell(letter, n).getChessFigure().getColor() != myColor) return;

        //if my figure
        emit highlightFigure(letter, n, true);
        isFigureChosen = true;
        currPos = currClick;
        //check turns
    }
    else {
        if (currPos == currClick) {
//          emit highlightFigure(currPos.first, currPos.second, false);
            isFigureChosen = false;
        }
        else if (getCell(letter, n).isCellEmpty()) {
            isFigureChosen = false;
            turn(currPos.first, currPos.second, letter, n);
        }
        else if (getCell(letter, n).getChessFigure().getColor() == myColor) {
            emit highlightFigure(currClick.first, currClick.second, true);
//            currPos = currClick;
        }
        else {
            turn(currPos.first, currPos.second, letter, n);
            //check turn
            isFigureChosen = false;
        }
        emit highlightFigure(currPos.first, currPos.second, false);
    }
    qDebug() << "end of process click";

}

void Game::getColor(QString color)
{
    if (color == QString("WHITE")) {
        qDebug() << "white";
        myColor = Color::WHITE;
    }
    else if (color == QString("BLACK")) {
        myColor = Color::BLACK;
        qDebug() << "black";
    }
}

Cell &Game::getCell(QChar letter, int n)
{
    int cast_index = correctIndex[n - 1];
    int letter_index = helpLetters.indexOf(letter);
//    qDebug() << "getCell() " << cast_index << letter_index;
    return field[cast_index][letter_index];
}

void Game::turn(QChar fromLetter, int fromN, QChar whereLetter, int whereN)
{
    qDebug() << "turn start";
    Figure figure = getCell(fromLetter, fromN).getChessFigure().getFigure();
    getCell(whereLetter, whereN).setChessFigure(getCell(fromLetter, fromN).getChessFigure());
    getCell(fromLetter, fromN).setCellEmpty();
//    emit needUpdate();
    emit madeTurn(figure, fromLetter, fromN, whereLetter, whereN);
}
