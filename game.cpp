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
    getCell(QChar('a'), 1).setChessFigure(new ChessFigureBoat(Color::WHITE));
    getCell(QChar('a'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));

    getCell(QChar('b'), 1).setChessFigure(new ChessFigureKnight(Color::WHITE));
    getCell(QChar('b'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));

    getCell(QChar('c'), 1).setChessFigure(new ChessFigureOfficer(Color::WHITE));
    getCell(QChar('c'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));

    getCell(QChar('d'), 1).setChessFigure(new ChessFigureQueen(Color::WHITE));
    getCell(QChar('d'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));

    getCell(QChar('e'), 1).setChessFigure(new ChessFigureKing(Color::WHITE));
    getCell(QChar('e'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));

    getCell(QChar('f'), 1).setChessFigure(new ChessFigureOfficer(Color::WHITE));
    getCell(QChar('f'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));

    getCell(QChar('g'), 1).setChessFigure(new ChessFigureKnight(Color::WHITE));
    getCell(QChar('g'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));

    getCell(QChar('h'), 1).setChessFigure(new ChessFigureBoat(Color::WHITE));
    getCell(QChar('h'), 2).setChessFigure(new ChessFigurePawn(Color::WHITE));
    //////////////////////////////////////////////////////////////////////////////
    getCell(QChar('a'), 8).setChessFigure(new ChessFigureBoat(Color::BLACK));
    getCell(QChar('a'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));

    getCell(QChar('b'), 8).setChessFigure(new ChessFigureKnight(Color::BLACK));
    getCell(QChar('b'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));

    getCell(QChar('c'), 8).setChessFigure(new ChessFigureOfficer(Color::BLACK));
    getCell(QChar('c'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));

    getCell(QChar('d'), 8).setChessFigure(new ChessFigureQueen(Color::BLACK));
    getCell(QChar('d'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));

    getCell(QChar('e'), 8).setChessFigure(new ChessFigureKing(Color::BLACK));
    getCell(QChar('e'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));

    getCell(QChar('f'), 8).setChessFigure(new ChessFigureOfficer(Color::BLACK));
    getCell(QChar('f'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));

    getCell(QChar('g'), 8).setChessFigure(new ChessFigureKnight(Color::BLACK));
    getCell(QChar('g'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));

    getCell(QChar('h'), 8).setChessFigure(new ChessFigureBoat(Color::BLACK));
    getCell(QChar('h'), 7).setChessFigure(new ChessFigurePawn(Color::BLACK));
}

void Game::processCellClick(QChar letter, int n) //logic
{
    qDebug() << letter << n;
    QPair<QChar, int> currClick = qMakePair(letter, n);
    if (!isFigureChosen) {
        if (getCell(letter, n).isCellEmpty()) return;
        else if (getCell(letter, n).getChessFigure()->getColor() != myColor) return;

        //if my figure
        emit highlightFigure(letter, n, true);
        isFigureChosen = true;
        currPos = currClick;
        //check turns
        possibleTurns.clear();
        auto f = simplification();
        if (myColor == Color::BLACK) rotateField(f);
        possibleTurns = getCell(letter, n).getChessFigure()->getPossibleTurns(f, currPos);
    }
    else {
        if (currPos == currClick) {
//          emit highlightFigure(currPos.first, currPos.second, false);
            isFigureChosen = false;
        }
        else if (getCell(letter, n).isCellEmpty()) {
            isFigureChosen = false;
            //if turns has point then turn
            turn(currPos.first, currPos.second, letter, n);
        }
        else if (getCell(letter, n).getChessFigure()->getColor() == myColor) {
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

void Game::setOpponentTurn(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN)
{
    ChessFigure *figure = getCell(fromLetter, fromN).getChessFigure();
    getCell(whereLetter, whereN).setChessFigure(figure);
    getCell(fromLetter, fromN).setCellEmpty();
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
    Figure figure = getCell(fromLetter, fromN).getChessFigure()->getFigure();
    getCell(whereLetter, whereN).setChessFigure(getCell(fromLetter, fromN).getChessFigure());
    getCell(fromLetter, fromN).setCellEmpty();
//    emit needUpdate();
    emit madeTurn(figure, fromLetter, fromN, whereLetter, whereN);
}

QVector<QVector<short> > Game::simplification()
{
    QVector<QVector<short> > simplificated(field.size());
    short temp = 0;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            if (field[i][j].isCellEmpty()) {
                temp = 0;
            }
            else if (field[i][j].getChessFigure()->getColor() == myColor) {
                if (field[i][j].getChessFigure()->getFigure() == Figure::KING)
                    temp = -2;
                else temp = -1;
            }
            else { //enemy figures
                if (field[i][j].getChessFigure()->getFigure() == Figure::KING)
                    temp = 2;
                else temp = 1;
            }
            simplificated[i].push_back(temp);
        }
    }
    return simplificated;
}
