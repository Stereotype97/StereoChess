#include "chesscontroller.h"

ChessController::ChessController(View *view, Game *game, QObject *parent) : QObject(parent)
{
    this->view = view;
    this->game = game;

    client = new UDPClient();

    connect(this->view, &View::readyToPlay, this, &ChessController::requestStartGame);

    connect(this->game, &Game::highlightFigure, this->view, &View::highlightFigure);
    connect(this->game, &Game::madeTurn, this, &ChessController::getTurnWithFigureFromGame);
    connect(this, &ChessController::sendTurnWithNameToView, this->view, &View::getTurnFromController);

    connect(this->view, &View::sendButtonNameToController, this, &ChessController::processButtonNameFromView);
    connect(this, &ChessController::sendCellToGame, this->game, &Game::processCellClick);

    connect(client, &UDPClient::sendConnectedState, this, &ChessController::setConnectedState);
    connect(client, &UDPClient::sendTurn, this->view, &View::showOpponentTurn);
    connect(client, &UDPClient::sendTurn, this->game, &Game::setOpponentTurn);
//    connect(this, &ChessController::sendTurnWithFigureToGame, this->game, &Game::setOpponentTurn);

    connect(client, &UDPClient::sendColor, this->game, &Game::getColor);
    connect(client, &UDPClient::sendColor, this->view, &View::buildField);

    connectionState = ConnectionState::DISCONNECTED;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ChessController::requestJoinToServer);
    timer->setInterval(1000);
    timer->start();

    initData();
}

void ChessController::initData()
{
    names.insert(Figure::BOAT,    "Л");
    names.insert(Figure::PAWN,    "П");
    names.insert(Figure::KNIGHT,  "К");
    names.insert(Figure::OFFICER, "С");
    names.insert(Figure::QUEEN,   "Ко");
    names.insert(Figure::KING,    "Кр");
}

void ChessController::requestJoinToServer()
{
    if (connectionState != ConnectionState::CONNECTED) {
        connectionState = ConnectionState::CONNECTING;
        client->WriteData(QString("I_AM_HERE"));
        qDebug() << "try connect to server";
    }
    else {
        qDebug() << "you've connected to server";
        timer->stop();
    }
}

void ChessController::requestStartGame()
{
    client->WriteData(QString("I_AM_READY"));
}

void ChessController::process()
{
    view->show();
}

void ChessController::processButtonNameFromView(QString buttonName)
{
    QStringList splittedString = buttonName.split("_"); //pattern: "cell_l_n"
    QChar letter = splittedString.at(1).at(0);
    int n = splittedString.at(2).toInt();
    emit sendCellToGame(letter, n);
}

void ChessController::getTurnWithFigureFromGame(Figure figure, QChar fromLetter, int fromN, QChar whereLetter, int whereN)
{
    QString name = names[figure];
    emit sendTurnWithNameToView(name, fromLetter, fromN, whereLetter, whereN);
    QString message = name + QString(" ");
    message.append(QString(fromLetter) + QString(" ") + QString::number(fromN) + QString(" "));
    message.append(QString(whereLetter) + QString(" ") + QString::number(whereN));
    client->WriteData(message);
}

//void ChessController::getTurnFromOpponent(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN)
//{
//    Figure figure = names.key(name);
//    emit sendTurnWithFigureToGame(figure, fromLetter, fromN, whereLetter, whereN);
//}

void ChessController::setConnectedState()
{
    connectionState = ConnectionState::CONNECTED;
}

