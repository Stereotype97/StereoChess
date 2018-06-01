#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <view.h>
#include <game.h>
#include <QObject>
#include <QTimer>
#include "udpclient.h"

#include <QMap>

class ChessController : public QObject
{
    Q_OBJECT

    enum class ConnectionState {DISCONNECTED, CONNECTING, CONNECTED};

    View *view;
    Game *game;

    ConnectionState connectionState;
    QTimer *timer;
    UDPClient *client;
    QMap<Figure, QString> names;

    void initData();

public:
    explicit ChessController(View *view, Game *game, QObject *parent = 0);
    void process();

signals:
    void sendCellToGame(QChar letter, int n);
    void sendTurnWithNameToView(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN);

public slots:
    void processButtonNameFromView(QString buttonName);
    void getTurnWithFigureFromGame(Figure figure, QChar fromLetter, int fromN, QChar whereLetter, int whereN);

    void requestJoinToServer();
    void setConnectedState();
    void requestStartGame();
};

#endif // CHESSCONTROLLER_H
