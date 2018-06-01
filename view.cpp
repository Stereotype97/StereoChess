#include "view.h"
#include "ui_view.h"
#include <QPushButton>
#include <QDebug>

View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    helpLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    helpIndex = {7, 6, 5, 4, 3, 2, 1, 0};

    setVisibleField(false);

    connect(ui->play, &QPushButton::clicked, this, &View::readyToPlay);
}

View::~View()
{
    delete ui;
}

void View::sendInfo()
{
    QObject *cell = sender();
    emit sendButtonNameToController(cell->objectName());
}

void View::highlightFigure(QChar letter, int n, bool isTurnOn)
{
    QPushButton *p = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(letter) + QString("_") + QString::number(n));
    QFont f = p->font();
    f.setBold(isTurnOn);
    p->setFont(f);
}

void View::getTurnFromController(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN)//добавить имя в параметры
{
    QPushButton *from = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(fromLetter) + QString("_") + QString::number(fromN));
    QPushButton *where = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(whereLetter) + QString("_") + QString::number(whereN));
    where->setText(name);
    from->setText("");
}

void View::showOpponentTurn(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN)
{
    QPushButton *from = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(fromLetter) + QString("_") + QString::number(fromN));
    QPushButton *where = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                            + QString(whereLetter) + QString("_") + QString::number(whereN));
    where->setText(name);
    from->setText("");
}

void View::buildField(QString color)
{
    qDebug() << "build field";
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
            connect(p, &QPushButton::clicked, this, &View::sendInfo);
            if (count % 2 == 0) {
                p->setStyleSheet("QPushButton { background-color: yellow }");
            }
            count++;
        }
        count++;
    }
    updateTable(getInitialField());
    showField();
}

void View::showField()
{
    ui->play->setVisible(false);
    setVisibleField(true);
}

QVector<QVector<QString > > View::getInitialField()
{
    QVector<QVector<QString > > field;
    QVector<QString> pawns(8, "П");
    QVector<QString> empty(8, "");

    //enemy figures
    field.push_back({"Л", "К", "О", "Ко", "Кр", "О", "К", "Л"});
    field.push_back(pawns);
    for (int i(0); i < 4; i++) {
        field.push_back(empty);
    }
    field.push_back(pawns);
    field.push_back({"Л", "К", "О", "Ко", "Кр", "О", "К", "Л"});

    return field;
}

void View::updateTable(QVector<QVector<QString> > field)
{
    for (int i(0); i < field.size(); i++) {
        for (int j(0); j < field[0].size(); j++) {
            QPushButton *p = ui->centralWidget->findChild<QPushButton *>(QString("cell_")
                                    + helpLetters[j] + QString("_") + QString::number(helpIndex.indexOf(i) + 1));
            p->setText(field[i][j]);
        }
    }
}

void View::setVisibleField(bool isNeedShow)
{
    for (QChar l : helpLetters) {
        for (int i(1); i <= 8; i++) {
            QPushButton *p = ui->centralWidget->findChild<QPushButton *>(QString("cell_") + l + QString("_") + QString::number(i));
            p->setVisible(isNeedShow);
        }
    }

    for (int i(1); i <= 8; i++) {
        QLabel *l = ui->centralWidget->findChild<QLabel *>(QString("l_") + QString::number(i));
        l->setVisible(isNeedShow);
    }

    for (int i(1), j(8); i <= 8; i++, j--) {
         QLabel *l = ui->centralWidget->findChild<QLabel *>(QString("n_") + QString::number(i));
         l->setVisible(isNeedShow);
    }
}
