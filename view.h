#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

    enum class Side {WHITE_SIDE, BLACK_SIDE};
public:
    explicit View(QWidget *parent = 0);
    ~View();
signals:
    void sendButtonNameToController(QString buttonName);
    void readyToPlay();

public slots:
    void highlightFigure(QChar letter, int n, bool isTurnOn);
    void getTurnFromController(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN);
    void showOpponentTurn(QString name, QChar fromLetter, int fromN, QChar whereLetter, int whereN);
    void buildField(QString color);
    void showField();

private slots:
    void sendInfo();
private:
    Ui::View *ui;

    QVector<QChar> helpLetters;
    QVector<int> helpIndex;

    void updateTable(QVector<QVector<QString> >);
    QVector<QVector<QString> > getInitialField();
    void setVisibleField(bool isNeedShow);
};

#endif // VIEW_H
