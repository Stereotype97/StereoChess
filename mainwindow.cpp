#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new UDPClient();

    connect(this, &MainWindow::sendCellToGame, &game, &Game::processClick);
    connect(&game, &Game::highlightFigure, this, &MainWindow::highlightFigure);
//    connect(&game, &Game::needUpdate, this, &MainWindow::updateTable);
    connect(&game, &Game::madeTurn, this, &MainWindow::getTurn);
    connect(client, &UDPClient::sendTurn, this, &MainWindow::getOpponentTurn);
    connect(client, &UDPClient::sendColor, &game, &Game::getColor);
    connect(client, &UDPClient::sendColor, this, &MainWindow::buildField);

    names.insert(Figure::BOAT,    "Л");
    names.insert(Figure::PAWN,    "П");
    names.insert(Figure::KNIGHT,  "К");
    names.insert(Figure::OFFICER, "С");
    names.insert(Figure::QUEEN,   "Ко");
    names.insert(Figure::KING,    "Кр");

    helpLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    helpIndex = {7, 6, 5, 4, 3, 2, 1, 0};

    client->WriteData(QString("I_AM_HERE"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendInfo()
{
    QObject *cell = sender();
    QString name = cell->objectName();
//    client->WriteData(name);
    QStringList splittedString = name.split("_"); //pattern: "cell_l_n"
    QChar letter = splittedString.at(1).at(0);
    int n = splittedString.at(2).toInt();
    emit sendCellToGame(letter, n);
}

void MainWindow::highlightFigure(QChar letter, int n, bool isTurnOn)
{
    QPushButton *p = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(letter) + QString("_") + QString::number(n));
    QFont f = p->font();
    f.setBold(isTurnOn);
    p->setFont(f);
}

void MainWindow::getTurn(QChar fromLetter, int fromN, QChar whereLetter, int whereN)
{
    QVector<QVector<Cell> > field = game.getField();
    QString nameOfFigure = names[field[helpIndex[whereN] + 1][helpLetters.indexOf(whereLetter)].getChessFigure().getFigure()];//README

    QPushButton *from = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(fromLetter) + QString("_") + QString::number(fromN));
    QPushButton *where = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(whereLetter) + QString("_") + QString::number(whereN));
    where->setText(nameOfFigure);
    from->setText("");

    QString message = nameOfFigure + QString(" ");
    message.append(QString(fromLetter) + QString(" ") + QString::number(fromN) + QString(" "));
    message.append(QString(whereLetter) + QString(" ") + QString::number(whereN));
    client->WriteData(message);
}

void MainWindow::getOpponentTurn(QChar fromLetter, int fromN, QChar whereLetter, int whereN)
{
    QVector<QVector<Cell> > field = game.getField();
    QString nameOfFigure = names[field[helpIndex[fromN - 1]][helpLetters.indexOf(fromLetter)].getChessFigure().getFigure()];//README

    QPushButton *from = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(fromLetter) + QString("_") + QString::number(fromN));
    QPushButton *where = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(whereLetter) + QString("_") + QString::number(whereN));
    where->setText(nameOfFigure);
    from->setText("");
}

void MainWindow::buildField(QString color)
{
    Side side;
    if (color == "WHITE") side = Side::WHITE_SIDE;
    else side = Side::BLACK_SIDE;

    if (side == Side::BLACK_SIDE) {
        //Replace buttons
        int leftX = 130;
        int leftY = 80;
        QVector<QChar> temp = {'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
        int shiftX(0), shiftY(0);
        for (QChar l : temp) {
            for (int i(1); i <= 8; i++) {
                QPushButton *p = ui->centralWidget->findChild<QPushButton *>(QString("cell_") + l + QString("_") + QString::number(i));
                p->setGeometry(leftX + shiftX, leftY + shiftY, 50, 50);
                shiftY += 50;
            }
            shiftX += 50;
            shiftY = 0;
        }

        //Rename labels
        int i(1);
        for (QChar letter : temp) {
            QLabel *l = ui->centralWidget->findChild<QLabel *>(QString("l_") + QString::number(i++));
            l->setText(QString(letter));
        }

        for (int i(1), j(8); i <= 8; i++, j--) {
             QLabel *l = ui->centralWidget->findChild<QLabel *>(QString("n_") + QString::number(i));
             l->setText(QString::number(j));
        }
    }

    int count = static_cast<int>(side);
    for (QChar l : helpLetters) {
        for (int i(1); i <= 8; i++) {
            QPushButton *p = ui->centralWidget->findChild<QPushButton *>(QString("cell_") + l + QString("_") + QString::number(i));
            connect(p, &QPushButton::clicked, this, &MainWindow::sendInfo);
            if (count % 2 == 0) {
                p->setStyleSheet("QPushButton { background-color: yellow }");
            }
            count++;
        }
        count++;
    }
    updateTable();
}

void MainWindow::updateTable()
{
    QVector<QVector<Cell> > field = game.getField();
    for (int i(0); i < field.size(); i++) {
        for (int j(0); j < field[0].size(); j++) {
            QPushButton *p = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                                    + helpLetters[j] + QString("_") + QString::number(helpIndex.indexOf(i) + 1));
            if (!field[i][j].isCellEmpty()) {
                p->setText(names[field[i][j].getChessFigure().getFigure()]);
            }
            else p->setText("");
        }
    }
}
