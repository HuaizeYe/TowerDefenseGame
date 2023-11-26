#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup(){
    this->setFixedSize(900,600);
    this->setWindowIcon(QPixmap(":/Icon4APproject/A3.png"));
    this->setWindowTitle("简笔塔防");
    ui->pushButtonStartGame->move(this->width()*0.5-ui->pushButtonStartGame->width()*0.5,this->height()*0.4);
    ui->pushButtonExit->move(this->width()*0.5-ui->pushButtonExit->width()*0.5,this->height()*0.4+100);
    ui->labelname->move(this->width()*0.5-ui->labelname->width()*0.5,this->height()*0.4-140);
    connect(ui->pushButtonExit,&QPushButton::clicked,[=](){
        this->close();
    });
    //点击开始游戏
    chooseLevel=new levelwindow;//选择关卡窗口
    connect(ui->pushButtonStartGame,&QPushButton::clicked,[=](){
        this->hide();
        chooseLevel->show();
    });
    connect(chooseLevel,&levelwindow::chooseBack,[=](){
        chooseLevel->hide();
        this->show();
    });
}
void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Icon4APproject/C.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
