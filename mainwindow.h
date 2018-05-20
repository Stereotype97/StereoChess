#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include "udpclient.h"
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum class Side {WHITE_SIDE, BLACK_SIDE};
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void sendCellToGame(QChar letter, int n);

private slots:
    void sendInfo();
    void highlightFigure(QChar letter, int n, bool isTurnOn);
    void getTurn(QChar fromLetter, int fromN, QChar whereLetter, int whereN);
    void getOpponentTurn(QChar fromLetter, int fromN, QChar whereLetter, int whereN);
    void buildField(QString color);
private:
    Ui::MainWindow *ui;
    Game game;
    UDPClient *client;

    QMap<Figure, QString> names;
    QVector<QChar> helpLetters;
    QVector<int> helpIndex;

    void updateTable();
};

#endif // MAINWINDOW_H
