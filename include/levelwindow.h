#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include"playscene.h"
#include<QPainter>
namespace Ui {
class levelwindow;
}

class levelwindow : public QMainWindow
{
    Q_OBJECT

public:
    playscene *play =NULL;
    explicit levelwindow(QWidget *parent = nullptr);
    ~levelwindow();
    void setup();
    void paintEvent(QPaintEvent*);
signals:
    void chooseBack();

private:
    Ui::levelwindow *ui;
};

#endif // LEVELWINDOW_H
