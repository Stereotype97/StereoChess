#include <QApplication>
#include <QDebug>
#include "chesscontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *game = new Game();
    View *view = new View();

    ChessController *chessController = new ChessController(view, game);
    chessController->process();

    return a.exec();
}
