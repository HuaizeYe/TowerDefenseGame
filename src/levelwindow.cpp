#include "levelwindow.h"
#include "ui_levelwindow.h"

levelwindow::levelwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::levelwindow)
{
    ui->setupUi(this);
    setup();
}

levelwindow::~levelwindow()
{
    delete ui;
}
void levelwindow::setup(){
    this->setFixedSize(900,600);
    this->setWindowIcon(QPixmap(":/Icon4APproject/A3.png"));
    this->setWindowTitle("简笔塔防—关卡选择");
    ui->label->move(this->width()*0.5-ui->label->width()*0.5,this->height()*0.1);
    ui->pushButtonBack->move(780,8);
    //设置返回按钮功能
    connect(ui->pushButtonBack,&QPushButton::clicked,[=](){
        emit this->chooseBack();
    });
    //添加关卡按钮
    for(int i=1;i<=8;i++){
        QPushButton * level =new QPushButton();
        level->setParent(this);
        QString path=":/Icon4APproject/D";
        QString end=".png";
        QString num=QString::number(i);
        QString final=path+num+end;
        //qDebug()<<final;
        QPixmap pix;
        pix.load(final);
        level->setFixedSize(100,100);
        level->setIcon(pix);
        level->setIconSize(QSize(100,100));
        level->setFlat(true);
        level->move((i-1)%4*120+230,(i-1)/4*120+200);
        connect(level,&QPushButton::clicked,[=](){
            qDebug()<<"你选择了第"<<i<<"关";
            play=new playscene(NULL,i);
            this->hide();
            play->show();
            connect(play,&playscene::chooseBack,[=](){
                play->hide();
                delete  play;
                play=NULL;
                this->show();
            });
        });
    }
}
void levelwindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Icon4APproject/C.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
