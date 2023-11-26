#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"levelwindow.h"
#include<QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    levelwindow *chooseLevel=NULL;
    MainWindow(QWidget *parent = nullptr);
    void setup();
    void paintEvent(QPaintEvent*);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
